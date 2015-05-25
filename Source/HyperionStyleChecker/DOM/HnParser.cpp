#include <HyperionStyleChecker/DOM/HnParser.h>

#include <Core/FileSystem/HnFileSystem.h>
#include <HyperionStyleChecker/DOM/HnParseSourceTask.h>
#include <tbb/tbb.h>

namespace HyperionStyleChecker
{
	HnParser::HnParser()
	{
	}

	HnParser::~HnParser()
	{
	}

	void HnParser::ParseSources(const std::vector<HnString> & crSourceFilePathes, std::vector<HnParsedFile> & rParsedFiles)
	{
		// Prepare values for the tasks.
		rParsedFiles.resize(crSourceFilePathes.size());

		// Create parse source tasks.
		std::vector<HnParseSourceTask> parseSourceTasks;
		for (int i = 0; i < crSourceFilePathes.size(); ++i)
		{
			parseSourceTasks.push_back(HnParseSourceTask(crSourceFilePathes[i], &rParsedFiles[i]));
		}

		// Launch all tasks and wait till they are completed.
		tbb::task_group taskGroup;
		for(int i = 0; i < parseSourceTasks.size(); ++i)
		{
			taskGroup.run(parseSourceTasks[i]);
		}
        taskGroup.wait();
	}
}