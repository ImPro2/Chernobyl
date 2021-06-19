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
		
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vb, const Ref<Shader>& shader) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ib) = 0;

		const Vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer()            const { return m_IndexBuffer;   }

	protected:
		Vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer>  m_IndexBuffer;
		uint32 m_VertexBufferIndex = 0;
	};

}