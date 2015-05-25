#include <QtCore/QCoreApplication>
#include <Core/Modules/ModuleManager.h>
#include <HyperionCheckService/Server/WebSocketServer.h>
#include <HyperionStyleChecker/StyleChecker/IStyleChecker.h>

using namespace Hyperion;
using namespace HyperionStyleChecker;

int main(int argc, char *argv[])
{
	IModule * pStyleCheckerModule = ModuleManager::Instance()->GetModule("HyperionStyleChecker");

	if (pStyleCheckerModule != nullptr)
	{
		IStyleChecker * pStyleChecker = nullptr;
		pStyleCheckerModule->CreateComponent("IStyleChecker", (void **)&pStyleChecker);

		if (pStyleChecker != nullptr)
		{
			pStyleChecker->Test();
		}
	}

	QCoreApplication a(argc, argv);

	WebSocketServer *server = new WebSocketServer(1234);
	QObject::connect(server, &WebSocketServer::closed, &a, &QCoreApplication::quit);

	return a.exec();
}
