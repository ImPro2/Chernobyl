#include "chpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace CH
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjMat(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMat(glm::mat4(1.0f))
	{
		m_ViewProjectionMat = m_ViewMat * m_ProjMat;
	}

	void OrthographicCamera::RecalculateMatrices()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMat = glm::inverse(transform);

		m_ViewProjectionMat = m_ViewMat * m_ProjMat;
	}

}