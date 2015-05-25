#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <HyperionStyleChecker/DOM/AST/HnMemberFunctionDef.h>
#include <HyperionStyleChecker/DOM/AST/HnMemberVariableDef.h>
#include <vector>

namespace HyperionStyleChecker
{
	class HnClassDef
	{
	public:
		HnClassDef();
		~HnClassDef();

		HnString sClassName;
		
		std::vector<HnMemberFunctionDef> memberFunctionDefs;
		std::vector<HnMemberVariableDef> memberVariableDefs;
	};
}