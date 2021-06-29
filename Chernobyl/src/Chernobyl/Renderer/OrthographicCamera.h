#pragma once

#include "Chernobyl/Core/Core.h"

#include <glm/glm.hpp>

namespace CH
{

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetPosition(float2 pos)     { m_Position = pos;					RecalculateMatrices(); }
		void SetRotation(float rotation) { m_Rotation = glm::radians(rotation);	RecalculateMatrices(); }

	private:
		void RecalculateMatrices();

	public:
		glm::mat4 GetViewMat()           const { return m_ViewMat; }
		glm::mat4 GetProjMat()           const { return m_ProjMat; }
		glm::mat4 GetViewProjectionMat() const { return m_ViewProjectionMat; }

	private:

		float2 m_Position = float2(0, 0);
		float m_Rotation = 0;

		glm::mat4 m_ViewMat;
		glm::mat4 m_ProjMat;
		glm::mat4 m_ViewProjectionMat;
	};

}