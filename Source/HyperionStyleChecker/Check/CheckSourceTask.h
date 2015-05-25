#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <HyperionStyleChecker/Check/CheckSourceResult.h>
#include <HyperionStyleChecker/DOM/HnParsedFile.h>

namespace HyperionStyleChecker
{
	class CheckSourceTask
	{
	public:
		CheckSourceTask();
		CheckSourceTask(const HnParsedFile * cpParsedFile, CheckSourceResult * pCheckSourceResult);
		~CheckSourceTask();

		void operator()() const;

	protected:
		const HnParsedFile * _cpParsedFile;
		CheckSourceResult * _pCheckSourceResult;
	};
}