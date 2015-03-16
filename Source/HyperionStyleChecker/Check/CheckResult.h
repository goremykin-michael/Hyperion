#pragma once

namespace HyperionStyleChecker
{
	class CheckResult
	{
	public:
		CheckResult() {}
		~CheckResult() {}

		string sCheckName;

		bool bIsOk;
		string sWhat;
	};
}