#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>

namespace Hyperion
{
	class HnProtectedMemberVariableNamingCheck : public HnICheck
	{
	public:
		HnProtectedMemberVariableNamingCheck() {}
		virtual ~HnProtectedMemberVariableNamingCheck() {}

		virtual HnString GetName()
		{
			return "Protected Member Variable Naming Check";
		};

		virtual HnCheckResult Check(const HnParsedFile * cpParsedFile)
		{
			HnCheckResult checkResult;
			checkResult.sCheckName = GetName();
			checkResult.bIsOk = true;

			for(int i = 0; i < cpParsedFile->classDefs.size(); ++i)
			{
				for(int j = 0; j < cpParsedFile->classDefs[i].memberVariableDefs.size(); ++j)
				{
					if(cpParsedFile->classDefs[i].memberVariableDefs[j].accessQualifier.sName == "protected")
					{
						// If the first letter of protected variable name is not '_'.
						if(cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName[0] != '_')
						{
							checkResult.bIsOk = false;
							checkResult.sWhat = "Protected variable names should start with \'_\' symbol: " + cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName;

							return checkResult;
						}
						// If protected name variable is in the upper case.
						else if(isupper(cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName[1]))
						{
							checkResult.bIsOk = false;
							checkResult.sWhat = "Protected variable names should be in lower case: " + cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName;

							return checkResult;
						}
					}
				}
			}

			return checkResult;
		}
	};
}