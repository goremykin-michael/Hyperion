#pragma once
#include <Core/Common/HnIncludes.h>

namespace HyperionStyleChecker
{
	class CheckResult
	{
	public:
		CheckResult() {}
		~CheckResult() {}

		HnString sCheckName;

		bool bIsOk;
		HnString sWhat;
	};
}