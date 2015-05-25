#include <Core/Modules/ModuleManager.h>

namespace Hyperion
{
	ModuleManager::ModuleManager()
	{
	}

	ModuleManager::~ModuleManager()
	{
	}

	IModule * ModuleManager::GetModule(const char * cpModuleName)
	{
		HnString sModuleName(cpModuleName);
		std::map<HnString, LoadedModule *>::iterator it = _loadedModules.find(sModuleName);

		if(it != _loadedModules.end())
		{
			return it->second;
		}
		else
		{
			HnString sModulePath(cpModuleName);
			void * pModuleSystemHandle = LoadModule(sModuleName);

			if(pModuleSystemHandle != nullptr)
			{
				//LogReport("ModuleManager::GetModule", "Successfully loaded module \"" + sModuleName + "\" located in \"" + sModulePath + "\"");

				GetModuleFuncPtr fpGetModule = (GetModuleFuncPtr)GetFunction(pModuleSystemHandle, "GetModule");
				if(fpGetModule != nullptr)
				{
					IModule * pModule = nullptr;
					fpGetModule(&pModule);

					if(pModule != nullptr)
					{
						LoadedModule * pLoadedModule = new LoadedModule(pModule, pModuleSystemHandle);

						_loadedModules[sModuleName] = pLoadedModule;
					
						return pLoadedModule;
					}
					else
					{
						//LogError("ModuleManager::GetModule", "Can't create IModule from module \"" + sModuleName + "\" located in \"" + sModulePath + "\"");
					}
				}
				else
				{
					//LogError("ModuleManager::GetModule", "Can't get function \"GetModule\" from module\"" + sModuleName + "\" located in \"" + sModulePath + "\"");
				}
			}
			else
			{
				//LogError("ModuleManager::GetModule", "Can't load module \"" + sModuleName + "\" located in \"" + sModulePath + "\"");
			}
		}

		return 0;
	}

	void * ModuleManager::LoadModule(HnString sModulePath)
	{
		HnString tmpName = sModulePath;

		tmpName += ".dll";

		int len;
		int slength = (int)tmpName.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, tmpName.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, tmpName.c_str(), slength, buf, len);
		std::wstring tmpTmpName(buf);
		delete[] buf;

		return (void*)LoadLibrary(tmpTmpName.c_str());
	}

	void * ModuleManager::GetFunction(void * pSharedModule, HnString sFunctionName)
	{
		return (void*)GetProcAddress((HINSTANCE)pSharedModule, sFunctionName.c_str());
	}

	bool ModuleManager::UnloadModule(void *pSharedModule)
	{
		return FreeLibrary((HINSTANCE)pSharedModule);
	}
}