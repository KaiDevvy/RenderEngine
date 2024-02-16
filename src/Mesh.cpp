#include "Mesh.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ModelImport.h"
#include <glm/gtc/quaternion.hpp>

std::vector<Mesh*> Mesh::all{};

Mesh::Mesh(std::string const& objName, bool isStatic)
{
	ModelImport::loadFromFile(*this, objName);

	all.push_back(this);
	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

Mesh::~Mesh()
{
	all.erase(std::remove(all.begin(), all.end(), this), all.end());
}

void Mesh::draw(glm::mat4 const& Perspective, glm::mat4 const& View, GLuint programID) const
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
	0,
	3,
	GL_FLOAT,
	GL_FALSE,
	0,
	(void*)0
	);

	// Normals
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(
	1,
	3,
	GL_FLOAT,
	GL_FALSE,
	0,
	(void*)0
	);

	
	glm::mat4 Translation = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 Rotation = glm::mat4_cast(glm::quat(glm::radians(rotation)));
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), scale);
	glm::mat4 ModelMatrix = Translation * Rotation * Scale;
	glm::mat4 MVP =  Perspective * View * ModelMatrix;

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDisableVertexAttribArray(0);
}

void Mesh::setPosition(glm::vec3 const& position)
{
	this->position = position;
}

glm::vec3 Mesh::getPosition() const
{
	return position;
}

void Mesh::setRotation(glm::vec3 const& rotation)
{
	this->rotation = rotation;
}

glm::vec3 Mesh::getRotation() const
{
	return rotation;
}

void Mesh::setScale(glm::vec3 const& scale)
{
	this->scale = scale;
}

glm::vec3 Mesh::getScale() const
{
	return scale;
}
