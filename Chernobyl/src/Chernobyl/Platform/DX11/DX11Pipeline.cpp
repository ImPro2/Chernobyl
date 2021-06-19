#include "chpch.h"
#include "DX11Pipeline.h"

#include "DX11Shader.h"

namespace CH {

	namespace Utils
	{
		DXGI_FORMAT ShaderDataTypeToDxgiFormat(Shader::DataType type)
		{
			switch (type)
			{
				case ShaderDataType::Float:		return DXGI_FORMAT_R32_FLOAT;
				case ShaderDataType::Float2:	return DXGI_FORMAT_R32G32_FLOAT;
				case ShaderDataType::Float3:	return DXGI_FORMAT_R32G32B32_FLOAT;
				case ShaderDataType::Float4:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
				case ShaderDataType::Int:		return DXGI_FORMAT_R32_SINT;
				case ShaderDataType::Int2:		return DXGI_FORMAT_R32G32_SINT;
				case ShaderDataType::Int3:		return DXGI_FORMAT_R32G32B32_SINT;
				case ShaderDataType::Int4:		return DXGI_FORMAT_R32G32B32A32_SINT;
				case ShaderDataType::Bool:		return DXGI_FORMAT_R8_TYPELESS;
				case ShaderDataType::Mat3:		break;
				case ShaderDataType::Mat4:		break;
			}

			CH_CORE_WARN("Unsupported shader data type");
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	DX11Pipeline::DX11Pipeline()
		: Pipeline()
	{
	}

	void DX11Pipeline::AddVertexBuffer(const Ref<VertexBuffer>& vb, const Ref<Shader>& shader)
	{
		Vector<D3D11_INPUT_ELEMENT_DESC> ieds;
		ID3D11InputLayout* inputLayout;

		vb->Bind();

		const auto& layout = vb->GetLayout();
		for (const auto& element : layout)
		{
			D3D11_INPUT_ELEMENT_DESC desc = { element.Name.c_str(), 0, Utils::ShaderDataTypeToDxgiFormat(element.Type), 0, (UINT)element.Offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
			ieds.push_back(desc);
		}

		DXInternal::GetDevice()->CreateInputLayout(ieds.data(), ieds.size(),
			static_cast<DX11Shader*>(shader.get())->GetVertexBlob()->GetBufferPointer(),
			static_cast<DX11Shader*>(shader.get())->GetVertexBlob()->GetBufferSize(),
			&inputLayout);

		DXInternal::GetDeviceContext()->IASetInputLayout(inputLayout);

		m_InputLayouts.push_back(inputLayout);
		m_VertexBufferIndex++;
	}

	void DX11Pipeline::Bind()
	{
		m_Binded = true;
	}

}