#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class FunctionNamingCheck : public ICheck
	{
	public:
		FunctionNamingCheck() {}
		virtual ~FunctionNamingCheck() {}

		virtual HnString GetName()
		{
			return "Function Naming Check";
		};

		virtual CheckResult Check(const HnParsedFile * cpParsedFile)
		{
			CheckResult checkResult;
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