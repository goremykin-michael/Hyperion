#include "HyperionCheckService/Server/WebSocketServer.h"

#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

#pragma comment(lib, "Qt5WebSocketsd")
#pragma comment(lib, "Qt5Networkd")

QT_USE_NAMESPACE

WebSocketServer::WebSocketServer(quint16 port, QObject *parent) :
QObject(parent),
m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
QWebSocketServer::NonSecureMode, this)),
m_clients()
{
	if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
		qDebug() << "WebSocketServer listening on port" << port;
		connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
		connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebSocketServer::closed);
	}

	iCountOfRecievedFiles = 0;
}

WebSocketServer::~WebSocketServer()
{
	m_pWebSocketServer->close();
	qDeleteAll(m_clients.begin(), m_clients.end());
}

void WebSocketServer::onNewConnection()
{
	QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

	connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processTextMessage);
	connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::processBinaryMessage);
	connect(pSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);

	m_clients << pSocket;
}

void WebSocketServer::processTextMessage(QString message)
{
	//printf("%s", message.toStdString().c_str());

	////int iReturnCode = (double)rand() / (RAND_MAX);
	//int iReturnCode = 1;

	//printf("%d\n", iReturnCode);

	//QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	//if (pClient) {
	//	pClient->sendTextMessage(QString::number(iReturnCode));
	//}

	arrayAccessMutex.lock();

	int iFilesCount = message.toInt();

	printf("Files count is %d", iFilesCount);

	filesToCheck.resize(iFilesCount);

	arrayAccessMutex.unlock();

	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient) {
		pClient->sendTextMessage(QString::number(3));
	}
}

void WebSocketServer::processBinaryMessage(QByteArray message)
{
	//int iReturnCode = (double)rand() / (RAND_MAX);
	//int iReturnCode = 1;

	//printf("%d\n", iReturnCode);

	arrayAccessMutex.lock();

	//printf("\nSent file %d bytes", message.size());
	filesToCheck[iCountOfRecievedFiles] = message;
	++iCountOfRecievedFiles;

	printf("\nRecieved %d of 3 files.", iCountOfRecievedFiles);

	if (iCountOfRecievedFiles == filesToCheck.size())
	{
		QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
		if (pClient) 
		{
			pClient->sendTextMessage(QString::number(0));
		}

		filesToCheck.reserve(0);
		iCountOfRecievedFiles = 0;
	}	

	arrayAccessMutex.unlock();
}

void WebSocketServer::socketDisconnected()
{
	printf("\nClient disconnected.");

	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient) {
		m_clients.removeAll(pClient);
		pClient->deleteLater();
	}
}
