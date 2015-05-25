#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class UsingGroupingCheck : public ICheck
	{
	public:
		UsingGroupingCheck() {}
		virtual ~UsingGroupingCheck() {}

		virtual HnString GetName()
		{
			return "Using Grouping Check";
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