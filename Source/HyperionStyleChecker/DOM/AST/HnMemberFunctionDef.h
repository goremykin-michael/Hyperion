#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/AST/HnAccessQualifier.h>
#include <HyperionStyleChecker/DOM/AST/HnFunctionDef.h>
#include <Core/Text/HnString.h>
#include <vector>

namespace HyperionStyleChecker
{
	class HnMemberFunctionDef
	{
	public:
		HnMemberFunctionDef();
		~HnMemberFunctionDef();

		HnAccessQualifier accessQualifier;
		HnFunctionDef functionDef;
	};
}