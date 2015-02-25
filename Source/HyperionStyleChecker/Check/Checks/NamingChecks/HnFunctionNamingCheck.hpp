#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>

namespace Hyperion
{
	class HnFunctionNamingCheck : public HnICheck
	{
	public:
		HnFunctionNamingCheck() {}
		virtual ~HnFunctionNamingCheck() {}

		virtual HnString GetName()
		{
			return "Function Naming Check";
		};

		virtual HnCheckResult Check(const HnParsedFile * cpParsedFile)
		{
			HnCheckResult checkResult;
			checkResult.sCheckName = GetName();
			checkResult.bIsOk = true;

			for(int i = 0; i < cpParsedFile->functionDefs.size(); ++i)
			{
				// If the first letter of class name is not in upper case.
				if(!isupper(cpParsedFile->functionDefs[i].sName[0]))
				{
					checkResult.bIsOk = false;
					checkResult.sWhat = "Lower case in function naming is not allowed: " + cpParsedFile->functionDefs[i].sName;

					return checkResult;
				}
				// If class name contains '_'-symbol.
				else if(cpParsedFile->functionDefs[i].sName.find('_') != -1)
				{
					checkResult.bIsOk = false;
					checkResult.sWhat = "Underscore symbol in function naming is not allowed: " + cpParsedFile->functionDefs[i].sName;

					return checkResult;
				}
			}
			
			return checkResult;
		}
	};
}