#include <Core/Modules/ModuleManager.h>
#include <HyperionCheckService/Service/ICheckService.h>

using namespace Hyperion;
using namespace HyperionCheckService;

void main()
{
	IModule * pCheckServiceModule = ModuleManager::Instance()->GetModule("HyperionCheckService");

	if (pCheckServiceModule != nullptr)
	{
		ICheckService * pCheckService = nullptr;
		pCheckServiceModule->CreateComponent("ICheckService", (void **)&pCheckService);

		if (pCheckService != nullptr)
		{
			pCheckService->Start();
		}
	}

	while(1);
}