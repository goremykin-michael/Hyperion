#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/Check/Checks/ICheck.h>
#include <vector>

namespace HyperionStyleChecker
{
	class HnCheckFactory
	{
	public:
		static void CreateChecks(std::vector<ICheck *> & rChecks);
		static void FreeChecks(std::vector<ICheck *> & rChecks);
	};
}