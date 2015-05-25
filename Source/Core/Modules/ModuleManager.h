#pragma once

#include <Core/DesignPatterns/HnSingleton.hpp>
#include <Core/Modules/IModuleManager.h>
#include <Core/Modules/LoadedModule.h>

#include <map>

namespace Hyperion
{
	class ModuleManager : public IModuleManager, public HnSingleton<ModuleManager>
	{
		friend class HnSingleton<ModuleManager>;

	public:
		//---------------------------IModuleManager---------------------------//
		virtual IModule * GetModule(const char * cpModuleName);

	protected:
		//---------------------------ModuleManager----------------------------//
		ModuleManager();
		~ModuleManager();

		void * LoadModule   (HnString sModulePath);
		void * GetFunction  (void * pSharedModule, HnString sFunctionName);
		bool   UnloadModule (void * pSharedModule);

		std::map<HnString, LoadedModule *> _loadedModules;
	};

	typedef int (*GetModuleFuncPtr)(Hyperion::IModule **);
}