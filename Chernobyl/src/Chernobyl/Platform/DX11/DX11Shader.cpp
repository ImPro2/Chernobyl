#include "chpch.h"
#include "DX11Shader.h"

#include <fstream>
#include <sstream>
#include <variant>

#include <d3dcompiler.h>

namespace CH {

	DX11Shader::DX11Shader(const String& str, Shader::Load mode)
	{
		auto [vertexSrc, pixelSrc] = Parse(str, mode);

		ID3DBlob* pVSBlob = Compile(vertexSrc, "VSMain", Shader::Type::Vertex);
		ID3DBlob* pPSBlob = Compile(pixelSrc, "PSMain", Shader::Type::Pixel);

		// create shader
		DXInternal::GetDevice()->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_VertexShader);
		DXInternal::GetDevice()->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_PixelShader);

		m_VertexShaderBlob = pVSBlob;

		Bind();
	}

	void DX11Shader::Bind()
	{
		DXInternal::GetDeviceContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		DXInternal::GetDeviceContext()->PSSetShader(m_PixelShader.Get(),  nullptr, 0);

		m_Binded = true;
	}

	Shader::ParseResult DX11Shader::Parse(const String& src, Shader::Load loadMode)
	{
		enum class Mode { None = -1, Vertex = 0, Pixel = 1 };

		std::stringstream ss[2];
		Mode mode = Mode::None;

		if (loadMode == Shader::Load::Source)
		{
			std::stringstream iss(src);

			std::string line;
			while (std::getline(iss, line))
			{
				if (line.find("#type vertex") != std::string::npos)
				{
					mode = Mode::Vertex;
				}
				else if (line.find("#type pixel") != std::string::npos || line.find("#type fragment") != std::string::npos)
				{
					mode = Mode::Pixel;
				}
				else
				{
					ss[(int32)mode] << line << '\n';
				}
			}
		}
		else if (loadMode == Shader::Load::Path)
		{
			std::ifstream in(src);

			CH_CORE_ASSERT(in.is_open(), "Invalid file path {0}", src);

			std::string line;
			while (std::getline(in, line))
			{
				if (line.find("#type vertex") != std::string::npos)
				{
					mode = Mode::Vertex;
				}
				else if (line.find("#type pixel") != std::string::npos || line.find("#type fragment") != std::string::npos)
				{
					mode = Mode::Pixel;
				}
				else
				{
					ss[(int32)mode] << line << '\n';
				}
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	ID3DBlob* DX11Shader::Compile(const String& src, const char* entrypoint, Shader::Type type)
	{
		const char* profile;

		switch (type)
		{
		case Shader::Type::Vertex:
			profile = "vs_4_0";
			break;
		case Shader::Type::Pixel:
			profile = "ps_4_0";
			break;
		default:
			CH_CORE_ASSERT(false, "Unknown shader type");
		}

		ID3DBlob* pErrBlob;
		ID3DBlob* pBlob;

		HRESULT hr = D3DCompile(src.c_str(), src.size(), nullptr, nullptr, nullptr, entrypoint, profile, D3DCOMPILE_DEBUG, NULL, &pBlob, &pErrBlob);

#define TO_STR(x) #x

		if (FAILED(hr))
		{
			pBlob->Release();
			const char* msg = (const char*)pErrBlob->GetBufferPointer();
			CH_CORE_ERROR("{0} Shader compilation failure:\n{1}", TO_STR(type), msg);
		}

		return pBlob;
	}

}