#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/HnCheckResult.h>
#include <vector>

namespace Hyperion
{
	class HnCheckFileResult
	{
	public:
		HnCheckFileResult() {}
		~HnCheckFileResult() {}

		HnString sParsedFilePath;
		std::vector<HnCheckResult> checkResults;
	};
}