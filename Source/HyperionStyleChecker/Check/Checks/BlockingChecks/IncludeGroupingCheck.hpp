#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class IncludeGroupingCheck : public ICheck
	{
	public:
		IncludeGroupingCheck() {}
		virtual ~IncludeGroupingCheck() {}

		virtual HnString GetName()
		{
			return "Include Grouping Check";
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