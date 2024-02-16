#pragma once
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ModelImport.h"

class RenderEngine
{
public:
	RenderEngine();

	void setPerspective(float FOV, float aspectRatio, float nearDist, float farDist);
	void setView(glm::mat4 const& newView);
	void draw();

private:
	

	glm::mat4 projection{};
	glm::mat4 view{};

	GLuint vertexBuffer{};
	GLuint normalBuffer{};
	GLuint programID{};
};
