#include <HyperionCheckService/Service/CheckService.h>
#include <HyperionCheckService/Server/WebSocketServer.h>

#include <QtCore/QCoreApplication>

namespace HyperionCheckService
{
	ThreadFunction ServiceThreadFunction(void * pData)
	{
		int argc = 1;
		char ** argv = (char **)malloc(sizeof(char *));
		argv[0] = (char *)malloc(sizeof(char) * 20);
		strcpy(argv[0], "Get some sleep");
		QCoreApplication a(argc, argv);

		WebSocketServer * pWebSocketServer = new WebSocketServer(1234);
		//QObject::connect(pWebSocketServer, &WebSocketServer::closed, &a, &QCoreApplication::quit);

		return a.exec();
	}

	void CheckService::Start()
	{
		_pThread = new Thread(&ServiceThreadFunction);
		_pThread->Start();
	}
}