#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class FunctionBracesSpacingCheck : public ICheck
	{
	public:
		FunctionBracesSpacingCheck() {}
		virtual ~FunctionBracesSpacingCheck() {}

		virtual HnString GetName()
		{
			return "Function Braces Spacing Check";
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