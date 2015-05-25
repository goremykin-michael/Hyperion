#pragma once
#include <HyperionStyleChecker/StyleChecker/IStyleChecker.h>

namespace HyperionStyleChecker
{
	class StyleChecker : IStyleChecker
	{
	public:
		virtual void Test();
	};
}