#include <QtCore/QCoreApplication>
#include <Core/Modules/ModuleManager.h>
#include <Core/Text/HnString.h>
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
			std::vector<CheckSourceResult> checkSourceResults;
			std::vector<HnString> fileNames{ HnString("D:\\Projects\\Hyperion\\Content\\code-samples\\c++\\QuestSystem\\Quest.cpp"),
											 HnString("D:\\Projects\\Hyperion\\Content\\code-samples\\c++\\QuestSystem\\Quest.h"),
											 HnString("D:\\Projects\\Hyperion\\Content\\code-samples\\c++\\QuestSystem\\QuestFactory.hpp"),
											 HnString("D:\\Projects\\Hyperion\\Content\\code-samples\\c++\\QuestSystem\\QuestIDs.h"),
											 HnString("D:\\Projects\\Hyperion\\Content\\code-samples\\c++\\QuestSystem\\QuestManager.cpp"),
											 HnString("D:\\Projects\\Hyperion\\Content\\code-samples\\c++\\QuestSystem\\QuestManager.h") };

			pStyleChecker->CheckFiles(fileNames, checkSourceResults);
		}
	}

	QCoreApplication a(argc, argv);

	WebSocketServer *server = new WebSocketServer(1234);
	QObject::connect(server, &WebSocketServer::closed, &a, &QCoreApplication::quit);

	return a.exec();
}
