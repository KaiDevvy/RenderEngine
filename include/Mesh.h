#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

class Mesh
{
public:
	static std::vector<Mesh*> all;

	Mesh(std::string const& objName, bool isStatic = false);
	~Mesh();

	void draw(glm::mat4 const& Perspective, glm::mat4 const& View, GLuint programID) const;

	void setPosition(glm::vec3 const& position);
	glm::vec3 getPosition() const;
	void setRotation(glm::vec3 const& rotation);
	glm::vec3 getRotation() const;
	void setScale(glm::vec3 const& scale);
	glm::vec3 getScale() const;

	bool enabled{true};

	GLuint vertexBuffer;
	GLuint normalBuffer;
	std::vector<unsigned int> vertexIndices{}, normalIndices{};
	std::vector<glm::vec3> vertices{};
	std::vector<glm::vec3> normals{};
private:
	glm::vec3 position{0,0,0};
	glm::vec3 rotation{0,0,0};
	glm::vec3 scale{1,1,1};
	bool isStatic;
};
