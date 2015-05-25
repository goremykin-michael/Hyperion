#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class DefineGroupingCheck : public ICheck
	{
	public:
		DefineGroupingCheck() {}
		virtual ~DefineGroupingCheck() {}

		virtual HnString GetName()
		{
			return "Define Grouping Check";
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