#pragma once

#define Shared __declspec(dllexport)

namespace Hyperion
{
	class IModule
	{
	public:
		virtual int CreateComponent(const char * pComponentName, void ** ppComponent) = 0;

	protected:
		virtual ~IModule() {}
	};
}

/// To be able create a module from a library, following method must be implemented:
/// extern "C" Shared int GetModule(Hyperion::IModule ** ppModule);