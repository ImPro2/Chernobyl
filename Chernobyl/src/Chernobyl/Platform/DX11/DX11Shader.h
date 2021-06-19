#pragma once

#include <unordered_map>

#include <d3d11shader.h>
#include <d3d11shadertracing.h>

#include "Chernobyl/Renderer/Shader.h"
#include "DX11Internal.h"

namespace CH {

	class DX11Shader : public Shader
	{
	public:
		DX11Shader(const String& str, Shader::Load mode);
		void Bind() override;

	public:
		ID3DBlob* GetVertexBlob() { return m_VertexShaderBlob.Get(); }

	private:
		Shader::ParseResult Parse(const String& src, Shader::Load loadMode);
		ID3DBlob* Compile(const String& src, const char* entrypoint, Shader::Type type);

	private:
		ComPtr<ID3D11VertexShader> m_VertexShader;
		ComPtr<ID3D11PixelShader>  m_PixelShader;

		ComPtr<ID3DBlob> m_VertexShaderBlob;
	};

}