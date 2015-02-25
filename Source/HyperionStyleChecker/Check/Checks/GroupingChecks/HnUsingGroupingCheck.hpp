#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>

namespace Hyperion
{
	class HnUsingGroupingCheck : public HnICheck
	{
	public:
		HnUsingGroupingCheck() {}
		virtual ~HnUsingGroupingCheck() {}

		virtual HnString GetName()
		{
			return "Using Grouping Check";
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