#include <HyperionStyleChecker/Module/HyperionStyleCheckerModule.h>
#include <HyperionStyleChecker/StyleChecker/StyleChecker.h>
#include <Core/Text/HnString.h>

extern "C" Shared int GetModule(Hyperion::IModule ** ppModule)
{
	*ppModule = new HyperionStyleChecker::HyperionStyleCheckerModule();

	return 0;
}

namespace HyperionStyleChecker
{
	HyperionStyleCheckerModule::HyperionStyleCheckerModule()
	{
	}

	HyperionStyleCheckerModule::~HyperionStyleCheckerModule()
	{
	}

	int HyperionStyleCheckerModule::CreateComponent(const char * pComponentName, void ** ppComponent)
	{
		if (HnString(pComponentName) == "IStyleChecker")
		{
			*ppComponent = new StyleChecker();
		}

		return 0;
	}
}