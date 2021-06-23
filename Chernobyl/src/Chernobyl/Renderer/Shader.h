#pragma once

#include "Chernobyl/Core/Core.h"
#include "RenderingResource.h"
#include "RendererAPISwitch.h"
#include "ShaderBuffer.h"

#include "ShaderTypes.h"

#include <glm/glm.hpp>

namespace CH {
		
	
	class Shader : public RenderingResource
	{
	public:
		static Ref<Shader> Create(const String& str, ShaderLoadMode mode);
		
		void SetBuffer(CH::Size size) { m_Buffer = ShaderBuffer::Create(size); }
		void SetBuffer(const Ref<ShaderBuffer>& buffer) { m_Buffer = buffer; }
		Ref<ShaderBuffer> GetBuffer() { return m_Buffer; }

	protected:
		Ref<ShaderBuffer> m_Buffer;
	};

	
}