#ifndef HNCLIENT_H
#define HNCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <qcoreapplication.h>
#include <qfile.h>

class HnClient : public QObject
{
	Q_OBJECT

public:
	HnClient(QObject *parent);
	~HnClient();

	void sendMessage(const QString & crMessage);
	void sendBinaryMessage(const QByteArray & crMessage);

	explicit HnClient(const QUrl &url, const QVector<QString> & crFileNames);

Q_SIGNALS:
	void closed();

private:
	void onConnected();
	void onMessageReceived(QString message);
	void onBinaryMessageReceived(QByteArray byteArray);
	void onErrorReceived(QString message);

	QWebSocket m_webSocket;
	QUrl m_url;
	QVector<QString> m_fileNames;
};

#endif // HNCLIENT_H
