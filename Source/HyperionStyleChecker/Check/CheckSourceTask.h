#pragma once
#include <Core/Common/HnIncludes.h>
#include <Core/Text/HnString.h>
#include <Checker/CPlusPlus/Check/HnCheckFileResult.h>
#include <Checker/CPlusPlus/Source/HnParsedFile.h>

namespace Hyperion
{
	class HnCheckFileTask
	{
	public:
		HnCheckFileTask();
		HnCheckFileTask(const HnParsedFile * cpParsedFile, HnCheckFileResult * pCheckFileResult);
		~HnCheckFileTask();

		void operator()() const;

	protected:
		const HnParsedFile * _cpParsedFile;
		HnCheckFileResult * _pCheckFileResult;
	};
}