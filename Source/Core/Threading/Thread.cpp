#include <Core/Threading/Thread.h>

namespace Hyperion
{
	Thread::Thread(DWORD (__stdcall * pFunction)(void*))
	{
		_pFunction = pFunction;
		_lpWinThreadID = NULL;
		_pData = 0;
	}

	Thread::Thread(DWORD (__stdcall * pFunction)(void*), void* pData)
	{
		_pFunction = pFunction;
		_lpWinThreadID = NULL;
		_pData = pData;
	}

	Thread::~Thread()
	{
	}

	int Thread::Start()
	{
		if(_pData == nullptr)
		{
			_hWinThread = CreateThread(0, 0, _pFunction, 0, 0, _lpWinThreadID);
		}
		else
		{
			_hWinThread = CreateThread(0, 0, _pFunction, _pData, 0, _lpWinThreadID);
		}

		if(_hWinThread != 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	int Thread::Suspend()
	{
		if(SuspendThread(_hWinThread)!= -1)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	int Thread::Resume()
	{
		if(ResumeThread(_hWinThread)!= -1)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	int Thread::Abort()
	{
		if(TerminateThread(_hWinThread, 0))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}