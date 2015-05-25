#ifndef WebSocketServer_H
#define WebSocketServer_H

#include <QObject>
#include <QVector>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

#include <windows.h>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)



class WebSocketServer : public QObject
{
	Q_OBJECT
public:
	explicit WebSocketServer(quint16 port, QObject *parent = Q_NULLPTR);
	~WebSocketServer();

Q_SIGNALS:
	void closed();

	private Q_SLOTS:
	void onNewConnection();
	void processTextMessage(QString message);
	void processBinaryMessage(QByteArray message);
	void socketDisconnected();

private:
	QWebSocketServer *m_pWebSocketServer;
	QList<QWebSocket *> m_clients;
	QVector<QByteArray> filesToCheck;

	int iCountOfRecievedFiles;
	QMutex arrayAccessMutex;
};


#endif // WebSocketServer_H
