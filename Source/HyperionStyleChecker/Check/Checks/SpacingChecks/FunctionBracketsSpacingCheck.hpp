#pragma once

namespace HyperionStyleChecker
{
	class FunctionBracketsSpacingCheck : public ICheck
	{
	public:
		FunctionBracketsSpacingCheck() {}
		virtual ~FunctionBracketsSpacingCheck() {}

		virtual String GetName()
		{
			return "Function Brackets Spacing Check";
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