#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <HyperionStyleChecker/Check/CheckResult.h>
#include <vector>

namespace HyperionStyleChecker
{
	class CheckSourceResult
	{
	public:
		CheckSourceResult() {}
		~CheckSourceResult() {}

		HnString sParsedFilePath;
		std::vector<CheckResult> checkResults;
	};
}