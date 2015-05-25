#pragma once
#include <Core/Modules/IModule.h>

extern "C" Shared int GetModule(Hyperion::IModule ** ppModule);

namespace Hyperion
{
	class CheckServiceModule : public IModule
	{
	public:
		CheckServiceModule();
		virtual ~CheckServiceModule();

		virtual int CreateComponent(const char * pComponentName, void ** ppComponent);
	};
}