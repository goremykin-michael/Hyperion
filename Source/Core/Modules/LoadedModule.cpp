#include <Core/Modules/LoadedModule.h>

namespace Hyperion
{
	LoadedModule::LoadedModule()
	{
		_pModule = nullptr;
		_pModuleSystemHandle = nullptr;
	}

	LoadedModule::LoadedModule(const LoadedModule & crLoadedModule)
	{
		_pModule = crLoadedModule._pModule;
		_pModuleSystemHandle = crLoadedModule._pModuleSystemHandle;
	}

	LoadedModule::LoadedModule(IModule * pModule, void * pModuleSystemHandle)
	{
		_pModule = pModule;
		_pModuleSystemHandle = pModuleSystemHandle;
	}

	LoadedModule::~LoadedModule()
	{
	}

	void LoadedModule::AddReference()
	{
		_iReferenceCount++;
	}

	void LoadedModule::Release()
	{
		_iReferenceCount--;
	}

	int LoadedModule::CreateComponent(const char * pComponentName, void ** ppComponent)
	{
		return _pModule->CreateComponent(pComponentName, ppComponent);
	}
}