#pragma once
#pragma once
#ifndef MVP_H
#define MVP_H
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"

class MVP
{
public:
	inline glm::mat4 CreateMVPMatrix(float FOVDegree, float windowWidth, float windowHeight) {
		this->m_windowHeight = windowHeight;
		this->m_windowWidth = windowWidth;
		this->m_FOVDegree = FOVDegree;
		glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(FOVDegree), m_windowWidth / m_windowHeight, 0.1f, 100.0f); 
		glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		glm::mat4 ModelMatrix = glm::mat4(1.0f);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		return MVP;
	}

	inline float GetfovDegree() { return m_FOVDegree; }
	inline glm::vec3* GetWindowHeight() { return &m_pos; }
	inline glm::vec3* GetRotation() { return &m_rotation; }
	inline glm::vec3* GetScale() { return &m_scale; }
	
	inline void SetFOVDegree(float FOVDegree) { this->m_FOVDegree = FOVDegree; }
	inline void SetWindowHeight(float height) { this->m_windowHeight = height; }
	inline void SetWindowWidth(float width) { this->m_windowWidth = width; }
	inline void SetScale(glm::vec3& scale) { this->m_scale = scale; }

private:
	float m_FOVDegree;
	float m_windowHeight;
	float m_windowWidth;
	glm::vec3 m_pos;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};

#endif;