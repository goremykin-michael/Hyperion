#pragma once

namespace HyperionStyleChecker
{
	class MemberFunctionNamingCheck : public ICheck
	{
	public:
		MemberFunctionNamingCheck() {}
		virtual ~MemberFunctionNamingCheck() {}

		virtual String GetName()
		{
			return "Member Function Naming Check";
		};

		virtual CheckResult Check(const ParsedFile * cpParsedFile)
		{
			CheckResult checkResult;
			checkResult.sCheckName = GetName();
			checkResult.bIsOk = true;

			for(int i = 0; i < cpParsedFile->classDefs.size(); ++i)
			{
				for(int j = 0; j < cpParsedFile->classDefs[i].memberFunctionDefs.size(); ++j)
				{
					// If the first letter of function name is not in upper case.
					if(!isupper(cpParsedFile->classDefs[i].memberFunctionDefs[j].functionDef.sName[0]))
					{
						checkResult.bIsOk = false;
						checkResult.sWhat = "Lower case in function naming is not allowed: " + cpParsedFile->classDefs[i].memberFunctionDefs[j].functionDef.sName;

						return checkResult;
					}
					// If class name contains '_'-symbol.
					else if(cpParsedFile->classDefs[i].memberFunctionDefs[j].functionDef.sName.find('_') != -1)
					{
						checkResult.bIsOk = false;
						checkResult.sWhat = "Underscore symbol in function naming is not allowed: " + cpParsedFile->classDefs[i].memberFunctionDefs[j].functionDef.sName;

						return checkResult;
					}
				}
			}

			return checkResult;
		}
	};
}