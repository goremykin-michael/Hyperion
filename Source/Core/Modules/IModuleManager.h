#pragma once
#include <Core/Modules/IModule.h>

namespace Hyperion
{
	class IModuleManager
	{
	public:
		virtual IModule * GetModule(const char * cpModuleName) = 0;
		
	protected:
		virtual ~IModuleManager() {}
	};
}