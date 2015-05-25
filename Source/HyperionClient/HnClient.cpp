#include "HnClient.h"
#include <QtCore/QDebug>

#pragma comment(lib, "Qt5WebSocketsd")

QT_USE_NAMESPACE

HnClient::HnClient(const QUrl &url, const QVector<QString> & crFileNames) :
	m_url(url)
{
	m_fileNames = crFileNames;

	connect(&m_webSocket, &QWebSocket::connected,           this, &HnClient::onConnected);
	connect(&m_webSocket, &QWebSocket::disconnected, this, &HnClient::closed);
	connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &HnClient::onMessageReceived);
	connect(&m_webSocket, &QWebSocket::binaryMessageReceived, this, &HnClient::onBinaryMessageReceived);
	m_webSocket.open(QUrl(url));
}



void HnClient::onConnected()
{
	qDebug() << "WebSocket connected";

	//QString message = "\nHello world!";

	//sendMessage(message.toStdString().c_str());

	//send all from m_fileNames
	sendMessage(QString::number(m_fileNames.size()));

	QFile* pFile;

	for each(auto item in m_fileNames)
	{
		pFile = new QFile(item);
		if (pFile->open(QIODevice::ReadOnly))
		{
			QByteArray blob = pFile->readAll();
			printf("\nSent file %d bytes", blob.size());
			sendBinaryMessage(blob.toStdString().c_str());
		}

		delete pFile;
	}
}

void HnClient::onMessageReceived(QString message)
{
	printf("\n%d", message.toInt());
	if (message.toInt() == 0)
	{
		//no errors
		//emit closed();
	}
	else if (message.toInt() == 1)
	{
		//QCoreApplication::instance()->exit(1);
	}
}

void HnClient::onBinaryMessageReceived(QByteArray byteArray)
{
	printf("1!");
}

void HnClient::sendMessage(const QString & crMessage)
{
	m_webSocket.sendTextMessage(crMessage);
}
void HnClient::sendBinaryMessage(const QByteArray & crMessage)
{
	m_webSocket.sendBinaryMessage(crMessage);
}

HnClient::~HnClient()
{

}