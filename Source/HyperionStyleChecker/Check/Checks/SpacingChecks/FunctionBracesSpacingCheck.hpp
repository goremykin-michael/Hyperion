#pragma once

namespace HyperionStyleChecker
{
	class FunctionBracesSpacingCheck : public ICheck
	{
	public:
		FunctionBracesSpacingCheck() {}
		virtual ~FunctionBracesSpacingCheck() {}

		virtual String GetName()
		{
			return "Function Braces Spacing Check";
		};

		virtual CheckResult Check(const ParsedFile * cpParsedFile)
		{
			CheckResult checkResult;
			checkResult.sCheckName = GetName();

			checkResult.bIsOk = true;

			return checkResult;
		}
	};
}