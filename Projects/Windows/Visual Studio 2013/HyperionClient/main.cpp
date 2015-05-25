
#include <QtCore/QCoreApplication>
#include <HyperionClient/HnClient.h>

int main(int argc, char *argv[])
{
	QVector<QString> fileNames{ QString("D:\\Projects\\HyperionTestingHooks\\1.txt"),
		QString("D:\\Projects\\HyperionTestingHooks\\2.txt"),
		QString("D:\\Projects\\HyperionTestingHooks\\3.txt") };

	QCoreApplication a(argc, argv);
	HnClient client(QUrl(QStringLiteral("ws://localhost:1234")), fileNames);
	QObject::connect(&client, &HnClient::closed, &a, &QCoreApplication::quit);

	return a.exec();
}
