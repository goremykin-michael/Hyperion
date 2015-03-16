// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

#include <HyperionStyleChecker/Check/Checks/ICheck.h>

using namespace HyperionStyleChecker;


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	//LineCharacterLengthCheck lineCharacterLengthCheck;
	//MultipleInheritanceCheck multipleInheritanceCheck;
	//IdenationFormattingCheck idenationFormattingCheck;
	FunctionCallLengthCheck callFunctionParameterLengthCheck;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

