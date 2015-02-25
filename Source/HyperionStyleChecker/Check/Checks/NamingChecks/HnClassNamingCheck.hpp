#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>

namespace Hyperion
{
	class HnClassNamingCheck : public HnICheck
	{
	public:
		HnClassNamingCheck() {}
		virtual ~HnClassNamingCheck() {}

		virtual HnString GetName()
		{
			return "Class Naming Check";
		};

		virtual HnCheckResult Check(const HnParsedFile * cpParsedFile)
		{
			HnCheckResult checkResult;
			checkResult.sCheckName = GetName();
			checkResult.bIsOk = true;

			for(int i = 0; i < cpParsedFile->classDefs.size(); ++i)
			{
				// If the first letter of class name is not in upper case.
				if(!isupper(cpParsedFile->classDefs[i].sClassName[0]))
				{
					checkResult.bIsOk = false;
					checkResult.sWhat = "Lower case in class naming is not allowed: " + cpParsedFile->classDefs[i].sClassName;

					return checkResult;
				}
				// If class name contains '_'-symbol.
				else if(cpParsedFile->classDefs[i].sClassName.find('_') != -1)
				{
					checkResult.bIsOk = false;
					checkResult.sWhat = "Underscore symbol in class naming is not allowed: " + cpParsedFile->classDefs[i].sClassName;

					return checkResult;
				}
			}

			return checkResult;
		}
	};
}