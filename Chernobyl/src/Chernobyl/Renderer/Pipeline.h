#pragma once
#include "Chernobyl/Core/Core.h"

#include "Buffer.h"
#include "Shader.h"

namespace CH {

	class Pipeline : public RenderingResource
	{
	public:
		static Ref<Pipeline> Create();
		Pipeline();
		
		virtual void SetVertexBuffer(const Ref<VertexBuffer>& vb, const Ref<Shader>& shader) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ib) = 0;

		const Ref<VertexBuffer>& GetVertexBuffer()           const { return m_VertexBuffer; }
		const Ref<IndexBuffer>&  GetIndexBuffer()            const { return m_IndexBuffer;   }

	protected:
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer>  m_IndexBuffer;
	};

}