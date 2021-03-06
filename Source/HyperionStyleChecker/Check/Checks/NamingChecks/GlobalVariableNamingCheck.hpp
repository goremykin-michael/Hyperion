#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class GlobalVariableNamingCheck : public ICheck
	{
	public:
		GlobalVariableNamingCheck() {}
		virtual ~GlobalVariableNamingCheck() {}

		virtual HnString GetName()
		{
			return "Global Variable Naming Check";
		};

		virtual CheckResult Check(const HnParsedFile * cpParsedFile)
		{
			CheckResult checkResult;
			checkResult.sCheckName = GetName();
			checkResult.bIsOk = true;

			for(int i = 0; i < cpParsedFile->globalVariableDefs.size(); ++i)
			{
				// If global variable name doesn't start with "g_".
				if(cpParsedFile->globalVariableDefs[i].sName[0] != 'g' || cpParsedFile->globalVariableDefs[i].sName[1] != '_')
				{
					checkResult.bIsOk = false;
					checkResult.sWhat = "The global variable name must start with \"g_\": " + cpParsedFile->globalVariableDefs[i].sName;

					return checkResult;
				}
				// If global variable name is in upper case.
				else if(isupper(cpParsedFile->globalVariableDefs[i].sName[2]))
				{
					checkResult.bIsOk = false;
					checkResult.sWhat = "The global variable name must be in lower case: " + cpParsedFile->globalVariableDefs[i].sName;

					return checkResult;
				}
			}
			
			return checkResult;
		}
	};
}