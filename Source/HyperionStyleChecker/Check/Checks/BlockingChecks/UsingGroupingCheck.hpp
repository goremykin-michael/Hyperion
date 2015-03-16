#pragma once

namespace HyperionStyleChecker
{
	class UsingGroupingCheck : public ICheck
	{
	public:
		UsingGroupingCheck() {}
		virtual ~UsingGroupingCheck() {}

		virtual String GetName()
		{
			return "Using Grouping Check";
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