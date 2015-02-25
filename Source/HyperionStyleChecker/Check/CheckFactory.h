#pragma once
#include <Core/Common/HnIncludes.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>
#include <vector>

namespace Hyperion
{
	class HnCheckFactory
	{
	public:
		static void CreateChecks(std::vector<HnICheck *> & rChecks);
		static void FreeChecks(std::vector<HnICheck *> & rChecks);
	};
}