#pragma once

namespace HyperionStyleChecker
{
	class PrivateMemberVariableNamingCheck : public ICheck
	{
	public:
		PrivateMemberVariableNamingCheck() {}
		virtual ~PrivateMemberVariableNamingCheck() {}

		virtual String GetName()
		{
			return "Private Member Variable Naming Check";
		};

		virtual CheckResult Check(const ParsedFile * cpParsedFile)
		{
			CheckResult checkResult;
			checkResult.sCheckName = GetName();
			checkResult.bIsOk = true;

			for(int i = 0; i < cpParsedFile->classDefs.size(); ++i)
			{
				for(int j = 0; j < cpParsedFile->classDefs[i].memberVariableDefs.size(); ++j)
				{
					if(cpParsedFile->classDefs[i].memberVariableDefs[j].accessQualifier.sName == "private")
					{
						// If the first letter of private variable name is not "__".
						if(cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName[0] != '_' || cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName[1] != '_')
						{
							checkResult.bIsOk = false;
							checkResult.sWhat = "Private variable names should start with \"__\": " + cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName;

							return checkResult;
						}
						// If private name variable is in the upper case.
						else if(isupper(cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName[2]))
						{
							checkResult.bIsOk = false;
							checkResult.sWhat = "Private variable names should be in lower case: " + cpParsedFile->classDefs[i].memberVariableDefs[j].variableDef.sName;

							return checkResult;
						}
					}
				}
			}

			return checkResult;
		}
	};
}