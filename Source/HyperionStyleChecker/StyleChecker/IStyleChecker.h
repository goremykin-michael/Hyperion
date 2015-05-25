#pragma once
#include <HyperionStyleChecker/Check/CheckSourceResult.h>
#include <vector>

using namespace HyperionStyleChecker;

namespace HyperionStyleChecker
{
	class IStyleChecker
	{
	public:
		virtual void CheckFiles(const std::vector<HnString> & crSourceFilePathes, std::vector<CheckSourceResult> & rCheckSourceResults) = 0;
	};
}