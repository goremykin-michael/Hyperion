#pragma once
#include <HyperionStyleChecker/StyleChecker/IStyleChecker.h>

namespace HyperionStyleChecker
{
	class StyleChecker : IStyleChecker
	{
	public:
		virtual void CheckFiles(const std::vector<HnString> & crSourceFilePathes, std::vector<CheckSourceResult> & rCheckSourceResults);
	};
}