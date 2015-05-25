#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class HnParseSourceTask
	{
	public:
		HnParseSourceTask();
		HnParseSourceTask(const HnString & crSourceFilePath, HnParsedFile * pParsedFile);
		~HnParseSourceTask();

		void operator()() const;

	protected:
		HnString _sSourceFilePath;

		HnParsedFile * _pParsedFile;
	};
}