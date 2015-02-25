#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/Checks/HnICheck.h>

namespace Hyperion
{
	class HnPublicMemberVariableNamingCheck : public HnICheck
	{
	public:
		HnPublicMemberVariableNamingCheck() {}
		virtual ~HnPublicMemberVariableNamingCheck() {}

		virtual HnString GetName()
		{
			return "Public Member Variable Naming Check";
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
					if(cpParsedFile->classDefs[i].memberVariableDefs[j].accessQualifier.sName == "public")
					{
						// If the first letter of public variable name is in upper case.
						if(isupper(cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName[0]))
						{
							checkResult.bIsOk = false;
							checkResult.sWhat = "Public variable names should start with lower case letter: " + cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName;

							return checkResult;
						}
					}
				}
			}

			return checkResult;
		}
	};
}