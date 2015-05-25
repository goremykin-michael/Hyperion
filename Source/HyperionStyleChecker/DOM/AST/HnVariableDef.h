#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>

namespace HyperionStyleChecker
{
	class HnClassDef;

	class HnVariableDef
	{
	public:
		HnVariableDef();
		~HnVariableDef();

		HnString sName;
		//HnClassDef classDef;
	};
}