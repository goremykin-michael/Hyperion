#include <HyperionCheckService/Module/CheckServiceModule.h>
#include <HyperionCheckService/Service/CheckService.h>
#include <Core/Text/HnString.h>

extern "C" Shared int GetModule(Hyperion::IModule ** ppModule)
{
	*ppModule = new Hyperion::CheckServiceModule();

	return 0;
}

namespace Hyperion
{
	CheckServiceModule::CheckServiceModule()
	{
	}

	CheckServiceModule::~CheckServiceModule()
	{
	}

	int CheckServiceModule::CreateComponent(const char * pComponentName, void ** ppComponent)
	{
		if(HnString(pComponentName) == "ICheckService")
		{
			*ppComponent = new HyperionCheckService::CheckService();
		}

		return 0;
	}
}