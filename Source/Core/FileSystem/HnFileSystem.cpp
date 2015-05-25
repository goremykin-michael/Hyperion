#include <Core/FileSystem/HnFileSystem.h>

#include <strsafe.h>

namespace Hyperion
{
	wchar_t* StringTowchar(const std::string & crString)
	{
		wchar_t* wString = NULL;

		int wchars_num =  MultiByteToWideChar( CP_UTF8 , 0 , crString.c_str() , -1, NULL , 0 );
		wString = new wchar_t[wchars_num];
		MultiByteToWideChar( CP_UTF8 , 0 , crString.c_str() , -1, wString , wchars_num );

		return wString;
	}

	void wstringToString(wchar_t * pWideString, std::string & rString)
	{
		char* str = NULL;

		int charNum = WideCharToMultiByte(CP_UTF8,0,pWideString,-1, NULL, 0, NULL, NULL);
		str = new char[charNum];
		WideCharToMultiByte(CP_UTF8, 0, pWideString, charNum, str, charNum, NULL, NULL);
		rString = str;

		delete [] str;
	}

	void HnFileSystem::GetListOfFilesInDirectory(const HnString & crDirectory, std::vector<HnString> & rFilePathes)
	{
		//TODO
		rFilePathes.push_back("../../cnt/code-samples/c++/QuestSystem/Quest.h");
		rFilePathes.push_back("../../cnt/code-samples/c++/QuestSystem/QuestManager.h");
		rFilePathes.push_back("../../cnt/code-samples/c++/QuestSystem/QuestFactory.hpp");
		rFilePathes.push_back("../../cnt/code-samples/c++/QuestSystem/QuestIDs.h");

		//std::vector<HnString> subDirectories;

		// Get pathes to all the files in the directory.
		//GetDirectoryInfoRecursive(crDirectory, subDirectories, rFilePathes);
	}

	void HnFileSystem::GetSingleDirectoryInfo(const HnString & crDirectoryPath, std::vector<HnString> & rSubDirectoryPathes, HnString & rPathPrefix, std::vector<HnString> & rFullNames)
	{
		WIN32_FIND_DATA ffd;
		LARGE_INTEGER filesize;
		TCHAR szDir[MAX_PATH];
		size_t length_of_arg;
		HANDLE hFind = INVALID_HANDLE_VALUE;

		HnString newPrefix;
		HnString sDirName,sFileName;

		wchar_t* wDirectoryPath = StringTowchar(crDirectoryPath);

			StringCchCopy(szDir, MAX_PATH, wDirectoryPath);

		delete [] wDirectoryPath;

		StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

		hFind = FindFirstFile(szDir, &ffd);

		if(!rPathPrefix.empty())
		{
			newPrefix = rPathPrefix;
		}

		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(ffd.cFileName[0] != '.')
				{
					wstringToString(ffd.cFileName, sDirName);
					rSubDirectoryPathes.push_back(rPathPrefix.empty() ? sDirName : (newPrefix + sDirName));
				}
			}
			else
			{
				filesize.LowPart = ffd.nFileSizeLow;
				filesize.HighPart = ffd.nFileSizeHigh;
    
				wstringToString(ffd.cFileName, sFileName);
				rFullNames.push_back(rPathPrefix.empty() ? sFileName : (newPrefix + sFileName));
			}
		}
		while (FindNextFile(hFind, &ffd) != 0);
	}

	void HnFileSystem::GetDirectoryInfoRecursive(const HnString & crDirectoryPath, std::vector<HnString> & rSubDirectoryPathes, std::vector<HnString> & rFullNames)
	{
		std::vector<HnString>& vSubDirectories = rSubDirectoryPathes;
		std::vector<HnString> newSubDirectories;
		HnString pathPrefix;
		HnString newPath;
		HnString newPrefix;

		if(vSubDirectories.empty())
		{
			GetSingleDirectoryInfo(crDirectoryPath, vSubDirectories, pathPrefix, rFullNames);
		}

		for(int i = 0 ; i < vSubDirectories.size(); ++i)
		{
			newPath = crDirectoryPath;
			newPath.append("\\");
			newPath.append(vSubDirectories[i]);

			newPrefix = vSubDirectories[i];
			newPrefix.append("\\");

			GetSingleDirectoryInfo(newPath, newSubDirectories, newPrefix, rFullNames);
		}

		if(!newSubDirectories.empty())
		{
			vSubDirectories.clear();
			vSubDirectories = newSubDirectories;

			GetDirectoryInfoRecursive(crDirectoryPath,vSubDirectories,rFullNames);
		}
	}
}
