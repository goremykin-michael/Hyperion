#pragma once
#include <HyperionCheckService/Service/ICheckService.h>
#include <Core/Threading/Thread.h>

using namespace Hyperion;

namespace HyperionCheckService
{
	class CheckService : ICheckService
	{
	public:
		virtual void Start();

	private:
		Thread * _pThread;
	};
}