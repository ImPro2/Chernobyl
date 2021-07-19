#pragma once

namespace CH
{

	enum class ExitCode
	{
		Success			= 0,
		FailedAssertion = 1,
		CustomExit		= 2 // like closing the application in code
	};

}