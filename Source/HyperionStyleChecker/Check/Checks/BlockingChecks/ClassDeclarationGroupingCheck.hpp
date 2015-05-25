#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class ClassDeclarationGroupingCheck : public ICheck
	{
	public:
		ClassDeclarationGroupingCheck() {}
		virtual ~ClassDeclarationGroupingCheck() {}

		HnString GetName()
		{
			return "Class Declaration Grouping Check";
		};

		CheckResult Check(const HnParsedFile * cpParsedFile)
		{
			CheckResult checkResult;
			checkResult.sCheckName = GetName();

			checkResult.bIsOk = true;

			return checkResult;
		}
	};
}