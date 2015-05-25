#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>
#include <vector>

namespace HyperionStyleChecker
{
	class HnParser
	{
	public:
		HnParser();
		~HnParser();

		static void ParseSources(const std::vector<HnString> & crSourceFilePathes, std::vector<HnParsedFile> & rParsedFiles);
	};
}