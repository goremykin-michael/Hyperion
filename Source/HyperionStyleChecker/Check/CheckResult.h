#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>

namespace Hyperion
{
	class HnCheckResult
	{
	public:
		HnCheckResult() {}
		~HnCheckResult() {}

		HnString sCheckName;

		bool bIsOk;
		HnString sWhat;
	};
}