#include <Checker/CPlusPlus/Check/HnCheckFileTask.h>

#include <Checker/CPlusPlus/Check/HnCheckFactory.h>

namespace Hyperion
{
	HnCheckFileTask::HnCheckFileTask() :
		_cpParsedFile(HnNullPointer), _pCheckFileResult(HnNullPointer)
	{
	}

	HnCheckFileTask::HnCheckFileTask(const HnParsedFile * cpParsedFile, HnCheckFileResult * pCheckFileResult)
	{
		_cpParsedFile = cpParsedFile;
		_pCheckFileResult = pCheckFileResult;
	}

	HnCheckFileTask::~HnCheckFileTask()
	{
	}

	void HnCheckFileTask::operator()() const
	{
		_pCheckFileResult->sParsedFilePath = _cpParsedFile->sFilePath;

		// Create checks.
		std::vector<HnICheck *> checks;
		HnCheckFactory::CreateChecks(checks);

		// Apply the checks.
		for(int i = 0; i < checks.size(); ++i)
		{
			_pCheckFileResult->checkResults.push_back(checks[i]->Check(_cpParsedFile));
		}

		// Free checks.
		HnCheckFactory::FreeChecks(checks);
	}
}