#pragma once

#include "RenderingResource.h"

namespace CH
{
	
	class Texture : public RenderingResource
	{
	public:
		uint32 GetWidth()  const { return m_Width;  }
		uint32 GetHeight() const { return m_Height; }

	protected:
		uint32 m_Width, m_Height;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const String& path);
		Texture2D(const String& path);

		void SetSlot(uint32 slot = 0) { m_Slot = slot; }

	protected:
		String m_Path;
		uint32 m_Slot;
	};

}