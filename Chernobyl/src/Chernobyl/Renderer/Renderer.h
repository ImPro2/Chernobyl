#pragma once

#include "RenderingResource.h"
#include "Buffer.h"
#include "Shader.h"
#include "ShaderBuffer.h"
#include "Pipeline.h"

#include "RenderCommand.h"
#include "RendererAPISwitch.h"

#include "OrthographicCamera.h"

#include "Chernobyl/Core/Application.h"
#include "Chernobyl/Core/Core.h"

namespace CH {

	class Renderer
	{
	public:
		static void Init();
		static void OnResize();
		
		static void BeginScene(const OrthographicCamera& camera);
		static void Submit(const Ref<Shader>& shader, const Ref<Pipeline>& pipeline, const glm::mat4& transform);
		static void EndScene();

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			Ref<ShaderBuffer> SysShaderBuffer;
		};
		static SceneData s_SceneData;
	};

}