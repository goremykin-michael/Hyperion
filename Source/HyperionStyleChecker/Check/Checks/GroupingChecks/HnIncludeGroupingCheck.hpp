#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>

namespace Hyperion
{
	class HnIncludeGroupingCheck : public HnICheck
	{
	public:
		HnIncludeGroupingCheck() {}
		virtual ~HnIncludeGroupingCheck() {}

		virtual HnString GetName()
		{
			return "Include Grouping Check";
		};

		virtual HnCheckResult Check(const HnParsedFile * cpParsedFile)
		{
			HnCheckResult checkResult;
			checkResult.sCheckName = GetName();

			checkResult.bIsOk = true;

			return checkResult;
		}
	};
}