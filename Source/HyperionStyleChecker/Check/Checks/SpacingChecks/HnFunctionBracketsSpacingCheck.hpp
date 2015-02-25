#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>

namespace Hyperion
{
	class HnFunctionBracketsSpacingCheck : public HnICheck
	{
	public:
		HnFunctionBracketsSpacingCheck() {}
		virtual ~HnFunctionBracketsSpacingCheck() {}

		virtual HnString GetName()
		{
			return "Function Brackets Spacing Check";
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