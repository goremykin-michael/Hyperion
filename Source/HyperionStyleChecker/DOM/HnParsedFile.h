#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <HyperionStyleChecker/DOM/AST/HnClassDef.h>
#include <HyperionStyleChecker/DOM/AST/HnFunctionDef.h>
#include <HyperionStyleChecker/DOM/AST/HnVariableDef.h>
#include <vector>

namespace HyperionStyleChecker
{
	class HnParsedFile
	{
	public:
		HnParsedFile();
		~HnParsedFile();

		HnString sFilePath;
		
		std::vector<HnClassDef> classDefs;
		std::vector<HnFunctionDef> functionDefs;
		std::vector<HnVariableDef> variableDefs;
		std::vector<HnVariableDef> globalVariableDefs;
	};
}