#include <Checker/CPlusPlus/Check/HnCheckFactory.h>

#include <Checker/CPlusPlus/Check/Checks/GroupingChecks/HnClassDeclarationGroupingCheck.hpp>
#include <Checker/CPlusPlus/Check/Checks/GroupingChecks/HnDefineGroupingCheck.hpp>
#include <Checker/CPlusPlus/Check/Checks/GroupingChecks/HnIncludeGroupingCheck.hpp>
#include <Checker/CPlusPlus/Check/Checks/GroupingChecks/HnUsingGroupingCheck.hpp>

#include <Checker/CPlusPlus/Check/Checks/NamingChecks/HnClassNamingCheck.hpp>
#include <Checker/CPlusPlus/Check/Checks/NamingChecks/HnFunctionNamingCheck.hpp>
#include <Checker/CPlusPlus/Check/Checks/NamingChecks/HnGlobalVariableNamingCheck.hpp>
#include <Checker/CPlusPlus/Check/Checks/NamingChecks/HnProtectedMemberVariableNamingCheck.hpp>
#include <Checker/CPlusPlus/Check/Checks/NamingChecks/HnPrivateMemberVariableNamingCheck.hpp>
#include <Checker/CPlusPlus/Check/Checks/NamingChecks/HnPublicMemberVariableNamingCheck.hpp>
#include <Checker/CPlusPlus/Check/Checks/NamingChecks/HnMemberFunctionNamingCheck.hpp>

#include <Checker/CPlusPlus/Check/Checks/SpacingChecks/HnFunctionBracesSpacingCheck.hpp>
#include <Checker/CPlusPlus/Check/Checks/SpacingChecks/HnFunctionBracketsSpacingCheck.hpp>

namespace Hyperion
{
	void HnCheckFactory::CreateChecks(std::vector<HnICheck *> & rChecks)
	{
		rChecks.push_back(new HnClassDeclarationGroupingCheck());
		rChecks.push_back(new HnDefineGroupingCheck());
		rChecks.push_back(new HnIncludeGroupingCheck());
		rChecks.push_back(new HnUsingGroupingCheck());
		
		rChecks.push_back(new HnClassNamingCheck());
		rChecks.push_back(new HnFunctionNamingCheck());
		rChecks.push_back(new HnGlobalVariableNamingCheck());
		rChecks.push_back(new HnProtectedMemberVariableNamingCheck());
		rChecks.push_back(new HnPrivateMemberVariableNamingCheck());
		rChecks.push_back(new HnPublicMemberVariableNamingCheck());
		rChecks.push_back(new HnMemberFunctionNamingCheck());
		
		rChecks.push_back(new HnFunctionBracesSpacingCheck());
		rChecks.push_back(new HnFunctionBracketsSpacingCheck());
	}

	void HnCheckFactory::FreeChecks(std::vector<HnICheck *> & rChecks)
	{
		for(int i = 0; i < rChecks.size(); ++i)
		{
			delete rChecks[i];
		}
	}
}