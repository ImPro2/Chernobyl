#pragma once

#include "Core.h"

namespace CH {

	class UUID
	{
	public:
		UUID() { Regenerate(); }
		String Regenerate();

	public:
		String Get() const { return m_UUID; }

	private:
		String m_UUID;
	};

}