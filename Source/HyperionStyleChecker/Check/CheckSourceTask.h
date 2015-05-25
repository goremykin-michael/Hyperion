#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <HyperionStyleChecker/Check/CheckResult.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class HnCheckFileTask
	{
	public:
		HnCheckFileTask();
		HnCheckFileTask(const HnParsedFile * cpParsedFile, CheckResult * pCheckFileResult);
		~HnCheckFileTask();

		void operator()() const;

	protected:
		const HnParsedFile * _cpParsedFile;
		CheckResult * _pCheckFileResult;
	};
}