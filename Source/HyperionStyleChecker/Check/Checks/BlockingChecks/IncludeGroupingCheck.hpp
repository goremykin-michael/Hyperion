#pragma once

namespace HyperionStyleChecker
{
	class IncludeGroupingCheck : public ICheck
	{
	public:
		IncludeGroupingCheck() {}
		virtual ~IncludeGroupingCheck() {}

		virtual String GetName()
		{
			return "Include Grouping Check";
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