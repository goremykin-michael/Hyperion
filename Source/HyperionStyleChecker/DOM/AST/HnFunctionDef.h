#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/AST/HnVariableDef.h>
#include <Core/Text/HnString.h>
#include <vector>

namespace HyperionStyleChecker
{
	class HnFunctionDef
	{
	public:
		HnFunctionDef();
		~HnFunctionDef();

		HnString sName;
		std::vector<HnVariableDef> parameters;
	};
}