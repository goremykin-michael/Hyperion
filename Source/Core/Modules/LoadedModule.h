#pragma once
#include <Core/Modules/IModule.h>

namespace Hyperion
{
	class LoadedModule : public IModule
	{
		friend class ModuleManager;

	public:
		//--------------------------------LoadedModule--------------------------------//
		LoadedModule();
		LoadedModule(const LoadedModule & crLoadedModule);
		~LoadedModule();
		
		void AddReference();
		void Release();

		//----------------------------------IModule----------------------------------//
		virtual int CreateComponent(const char * pComponentName, void ** ppComponent);

	protected:
		LoadedModule(IModule * pModule, void * pModuleSystemHandle);

		IModule * _pModule;
		int _iReferenceCount;

		void * _pModuleSystemHandle;
	};
}