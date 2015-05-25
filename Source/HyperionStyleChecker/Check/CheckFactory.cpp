#include <HyperionStyleChecker/Check/CheckFactory.h>

#include <HyperionStyleChecker/Check/Checks/BlockingChecks/ClassDeclarationGroupingCheck.hpp>
#include <HyperionStyleChecker/Check/Checks/BlockingChecks/DefineGroupingCheck.hpp>
#include <HyperionStyleChecker/Check/Checks/BlockingChecks/IncludeGroupingCheck.hpp>
#include <HyperionStyleChecker/Check/Checks/BlockingChecks/UsingGroupingCheck.hpp>

#include <HyperionStyleChecker/Check/Checks/NamingChecks/ClassNamingCheck.hpp>
#include <HyperionStyleChecker/Check/Checks/NamingChecks/FunctionNamingCheck.hpp>
#include <HyperionStyleChecker/Check/Checks/NamingChecks/GlobalVariableNamingCheck.hpp>
#include <HyperionStyleChecker/Check/Checks/NamingChecks/ProtectedMemberVariableNamingCheck.hpp>
#include <HyperionStyleChecker/Check/Checks/NamingChecks/PrivateMemberVariableNamingCheck.hpp>
#include <HyperionStyleChecker/Check/Checks/NamingChecks/PublicMemberVariableNamingCheck.hpp>
#include <HyperionStyleChecker/Check/Checks/NamingChecks/MemberFunctionNamingCheck.hpp>

#include <HyperionStyleChecker/Check/Checks/SpacingChecks/FunctionBracesSpacingCheck.hpp>
#include <HyperionStyleChecker/Check/Checks/SpacingChecks/FunctionBracketsSpacingCheck.hpp>

namespace HyperionStyleChecker
{
	void HnCheckFactory::CreateChecks(std::vector<ICheck *> & rChecks)
	{
		rChecks.push_back(new ClassDeclarationGroupingCheck());
		rChecks.push_back(new DefineGroupingCheck());
		rChecks.push_back(new IncludeGroupingCheck());
		rChecks.push_back(new UsingGroupingCheck());
		
		rChecks.push_back(new ClassNamingCheck());
		rChecks.push_back(new FunctionNamingCheck());
		rChecks.push_back(new GlobalVariableNamingCheck());
		rChecks.push_back(new ProtectedMemberVariableNamingCheck());
		rChecks.push_back(new PrivateMemberVariableNamingCheck());
		rChecks.push_back(new PublicMemberVariableNamingCheck());
		rChecks.push_back(new MemberFunctionNamingCheck());
		
		rChecks.push_back(new FunctionBracesSpacingCheck());
		rChecks.push_back(new FunctionBracketsSpacingCheck());
	}

	void HnCheckFactory::FreeChecks(std::vector<ICheck *> & rChecks)
	{
		for(int i = 0; i < rChecks.size(); ++i)
		{
			delete rChecks[i];
		}
	}
}