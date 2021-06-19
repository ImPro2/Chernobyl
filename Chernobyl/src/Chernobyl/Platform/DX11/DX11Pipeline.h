#pragma once
#include "Chernobyl/Renderer/Pipeline.h"

#include "DX11Internal.h"

namespace CH {

	class DX11Pipeline : public Pipeline
	{
	public:
		DX11Pipeline();

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vb, const Ref<Shader>& shader) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ib) override { m_IndexBuffer = ib; }

		void Bind() override;

	private:
		Vector<ComPtr<ID3D11InputLayout>> m_InputLayouts;
	};

}