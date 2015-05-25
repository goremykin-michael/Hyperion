#pragma once
#include <Core/Modules/IModule.h>

extern "C" Shared int GetModule(Hyperion::IModule ** ppModule);

namespace HyperionStyleChecker
{
	class HyperionStyleCheckerModule : public Hyperion::IModule
	{
	public:
		HyperionStyleCheckerModule();
		virtual ~HyperionStyleCheckerModule();

		virtual int CreateComponent(const char * pComponentName, void ** ppComponent);
	};
}
