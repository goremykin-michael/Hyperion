#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>

namespace Hyperion
{
	class HnFunctionBracesSpacingCheck : public HnICheck
	{
	public:
		HnFunctionBracesSpacingCheck() {}
		virtual ~HnFunctionBracesSpacingCheck() {}

		virtual HnString GetName()
		{
			return "Function Braces Spacing Check";
		};

		virtual HnCheckResult Check(const HnParsedFile * cpParsedFile)
		{
			HnCheckResult checkResult;
			checkResult.sCheckName = GetName();

			checkResult.bIsOk = true;

			return checkResult;
		}
	};
}