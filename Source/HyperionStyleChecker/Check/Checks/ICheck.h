#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/HnCheckResult.h>
#include <Checker/CPlusPlus/Source/HnParsedFile.h>

namespace Hyperion
{
	class HnICheck
	{
	public:
		virtual ~HnICheck() {}

		virtual HnString GetName() = 0;
		virtual HnCheckResult Check(const HnParsedFile * cpParsedFile) = 0;
	};
}