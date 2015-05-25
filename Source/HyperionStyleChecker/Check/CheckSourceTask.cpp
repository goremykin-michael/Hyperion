#include <HyperionStyleChecker/Check/CheckSourceTask.h>

#include <HyperionStyleChecker/Check/CheckFactory.h>

namespace HyperionStyleChecker
{
	CheckSourceTask::CheckSourceTask() :
		_cpParsedFile(HnNullPointer), _pCheckSourceResult(HnNullPointer)
	{
	}

	CheckSourceTask::CheckSourceTask(const HnParsedFile * cpParsedFile, CheckSourceResult * pCheckSourceResult)
	{
		_cpParsedFile = cpParsedFile;
		_pCheckSourceResult = pCheckSourceResult;
	}

	CheckSourceTask::~CheckSourceTask()
	{
	}

	void CheckSourceTask::operator()() const
	{
		_pCheckSourceResult->sParsedFilePath = _cpParsedFile->sFilePath;

		// Create checks.
		std::vector<ICheck *> checks;
		HnCheckFactory::CreateChecks(checks);

		// Apply the checks.
		for(int i = 0; i < checks.size(); ++i)
		{
			_pCheckSourceResult->checkResults.push_back(checks[i]->Check(_cpParsedFile));
		}

		// Free checks.
		HnCheckFactory::FreeChecks(checks);
	}
}