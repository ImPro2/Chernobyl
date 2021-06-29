#pragma once

#include "Chernobyl/Core/Core.h"

namespace CH {

	namespace RenderingResourceType
	{
		enum : u16
		{
			None    =     0,
			Shader  = BIT(1),
			Texture = BIT(2),
			Buffer  = BIT(3)
		};
	}

	class RendererVault;

	// all classes like VertexBuffer, Shader, etc. derived from this class
	class RenderingResource
	{
	public:
		using Type = u16;

	public:
		virtual ~RenderingResource() = default;
		virtual void Bind() = 0;

	public:
		bool IsBinded()  const { return m_Binded; }
		String GetUUID() const { return m_UUID;   }
		String GetName() const { return m_Name;   }
		Type GetType()   const { return m_Type;   }

	protected:
		bool m_Binded = false;
		String m_UUID;
		String m_Name;
		Type m_Type;
	private:
		friend class RendererVault;
	};

	// storage for rendering resources

	class RendererVault
	{
	public:
		static void Submit(const std::shared_ptr<RenderingResource>& resource);
		static Ref<RenderingResource>& GetResource(String uuid);
		
		template<RenderingResource::Type T>
		static Ref<RenderingResource>& GetResource(const String& name);

	private:
		static Vector<Ref<RenderingResource>> s_Resources;
	};

}