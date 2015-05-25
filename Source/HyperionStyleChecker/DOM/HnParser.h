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

		static void ParseSourceFromDirectory(const HnString & crDirectory, std::vector<HnParsedFile> & rParsedFiles);
	};
}