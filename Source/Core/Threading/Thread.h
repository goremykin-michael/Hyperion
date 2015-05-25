#pragma once
#include "windows.h"

#define ThreadFunction DWORD __stdcall

namespace Hyperion
{
	class Thread
	{		
	public:
		Thread(DWORD (__stdcall * pFunction)(void*));
		Thread(DWORD (__stdcall * pFunction)(void*), void* pData);
		~Thread();

		int Start();
		int Suspend();
		int Resume();
		int Abort();

	private:
		DWORD (__stdcall * _pFunction)(void*);
		
		HANDLE _hWinThread;
		LPDWORD _lpWinThreadID;

		void * _pData;
	};
}