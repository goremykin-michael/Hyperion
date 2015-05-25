#pragma once
#include <Core/Common/HnIncludes.h>
#include <HyperionStyleChecker/DOM/AST/HnAccessQualifier.h>
#include <HyperionStyleChecker/DOM/AST/HnVariableDef.h>
#include <Core/Text/HnString.h>

namespace HyperionStyleChecker
{
	class HnMemberVariableDef
	{
	public:
		HnMemberVariableDef();
		~HnMemberVariableDef();

		HnAccessQualifier accessQualifier;
		HnVariableDef variableDef;
	};
}