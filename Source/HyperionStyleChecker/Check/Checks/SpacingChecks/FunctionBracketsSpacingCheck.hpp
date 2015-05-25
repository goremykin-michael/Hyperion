#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class FunctionBracketsSpacingCheck : public ICheck
	{
	public:
		FunctionBracketsSpacingCheck() {}
		virtual ~FunctionBracketsSpacingCheck() {}

		virtual HnString GetName()
		{
			return "Function Brackets Spacing Check";
		};

		virtual CheckResult Check(const HnParsedFile * cpParsedFile)
		{
			CheckResult checkResult;
			checkResult.sCheckName = GetName();

			checkResult.bIsOk = true;

			return checkResult;
		}
	};
}