#include <HyperionStyleChecker/StyleChecker/StyleChecker.h>
#include <HyperionStyleChecker/DOM/HnParser.h>

#include <HyperionStyleChecker/Check/CheckSourceTask.h>
#include <tbb/tbb.h>

namespace HyperionStyleChecker
{
	void StyleChecker::CheckFiles(const std::vector<HnString> & crSourceFilePathes, std::vector<CheckSourceResult> & rCheckSourceResults)
	{
		std::vector<HnParsedFile> parsedFiles;

		// Parse sources.
		HnParser::ParseSources(crSourceFilePathes, parsedFiles);

		// Prepare values for the tasks.
		rCheckSourceResults.resize(parsedFiles.size());

		// Create check-source tasks.
		std::vector<CheckSourceTask> checkFileTasks;
		for (int i = 0; i < parsedFiles.size(); ++i)
		{
			checkFileTasks.push_back(CheckSourceTask(&parsedFiles[i], &rCheckSourceResults[i]));
		}

		// Launch all tasks and wait till they are completed.
		tbb::task_group taskGroup;
		for (int i = 0; i < checkFileTasks.size(); ++i)
		{
			taskGroup.run(checkFileTasks[i]);
		}
		taskGroup.wait();
	}
}