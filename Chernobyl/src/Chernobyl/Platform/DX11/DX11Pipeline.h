#pragma once
#include "Chernobyl/Renderer/Pipeline.h"

#include "DX11Internal.h"

namespace CH {

	class DX11Pipeline : public Pipeline
	{
	public:
		DX11Pipeline();

		virtual void SetVertexBuffer(const Ref<VertexBuffer>& vb, const Ref<Shader>& shader) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ib) override { m_IndexBuffer = ib; }

		void Bind() override;

	private:
		ComPtr<ID3D11InputLayout> m_InputLayout;
	};

}