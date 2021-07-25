#pragma once

#include "Systems/TimeSystem/TimeSystem.hpp"

namespace CH
{

	class WindowsTimeSystem : public TimeSystem
	{
	public:
		void Init() override;
		void Shutdown() override;
	};

}