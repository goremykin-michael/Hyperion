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

	void HnParser::ParseSourceFromDirectory(const HnString & crDirectory, std::vector<HnParsedFile> & rParsedFiles)
	{
		std::vector<HnString> sourceFilePathes;

		//// Get list of source files in directory.
		//HnFileSystem::GetListOfFilesInDirectory(crDirectory, sourceFilePathes);

		//// Prepare values for the tasks.
		//rParsedFiles.resize(sourceFilePathes.size());

		//// Create parse source tasks.
		//std::vector<HnParseSourceTask> parseSourceTasks;
		//for(int i = 0; i < sourceFilePathes.size(); ++i)
		//{
		//	parseSourceTasks.push_back(HnParseSourceTask(sourceFilePathes[i], &rParsedFiles[i]));
		//}

		//// Launch all tasks and wait till they are completed.
		//tbb::task_group taskGroup;
		//for(int i = 0; i < parseSourceTasks.size(); ++i)
		//{
		//	taskGroup.run(parseSourceTasks[i]);
		//}
  //      taskGroup.wait();
	}
}