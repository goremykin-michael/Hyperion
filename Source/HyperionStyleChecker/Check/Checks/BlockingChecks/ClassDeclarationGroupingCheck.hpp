#pragma once

namespace HyperionStyleChecker
{
	class ClassDeclarationGroupingCheck : public ICheck
	{
	public:
		ClassDeclarationGroupingCheck() {}
		virtual ~ClassDeclarationGroupingCheck() {}

		virtual String GetName()
		{
			return "Class Declaration Grouping Check";
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