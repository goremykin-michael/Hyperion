#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>

namespace Hyperion
{
	class HnClassDeclarationGroupingCheck : public HnICheck
	{
	public:
		HnClassDeclarationGroupingCheck() {}
		virtual ~HnClassDeclarationGroupingCheck() {}

		virtual HnString GetName()
		{
			return "Class Declaration Grouping Check";
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