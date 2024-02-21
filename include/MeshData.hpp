#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>


class MeshData
{
public:
	GLuint vertexBuffer;
	GLuint normalBuffer;
	std::vector<unsigned int> vertexIndices{}, normalIndices{};
	std::vector<glm::vec3> vertices{};
	std::vector<glm::vec3> normals{};
	glm::vec3 color{};
};
