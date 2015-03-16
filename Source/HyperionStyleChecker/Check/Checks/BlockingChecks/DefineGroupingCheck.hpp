#pragma once

namespace HyperionStyleChecker
{
	class DefineGroupingCheck : public ICheck
	{
	public:
		DefineGroupingCheck() {}
		virtual ~DefineGroupingCheck() {}

		virtual String GetName()
		{
			return "Define Grouping Check";
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