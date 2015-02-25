#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>

namespace Hyperion
{
	class HnDefineGroupingCheck : public HnICheck
	{
	public:
		HnDefineGroupingCheck() {}
		virtual ~HnDefineGroupingCheck() {}

		virtual HnString GetName()
		{
			return "Define Grouping Check";
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