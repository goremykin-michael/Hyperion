#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <vector>

namespace HyperionStyleChecker
{
	class HnFileSystem
	{
	public:
		static void GetListOfFilesInDirectory(const HnString & crDirectory, std::vector<HnString> & rFilePathes);

	protected:
		/// Get info about single directory.
		static void GetSingleDirectoryInfo(const HnString & crDirectoryPath, std::vector<HnString> & rSubDirectoryPathes, HnString & rPathPrefix, std::vector<HnString> & rFullNames);

		/// Traverse throught directory hierarchy and obtain directory info.
		static void GetDirectoryInfoRecursive(const HnString & crDirectoryPath, std::vector<HnString> & rSubDirectoryPathes, std::vector<HnString> & rFullNames);
	};
}