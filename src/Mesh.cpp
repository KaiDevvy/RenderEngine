#include "Mesh.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ModelImport.h"
#include <glm/gtc/quaternion.hpp>

std::vector<Mesh*> Mesh::all{};

Mesh::Mesh(std::string const& objName, bool isStatic)
{
	data = ModelImport::loadFromFile(objName);

	all.push_back(this);

	glGenBuffers(1, &data->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, data->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, data->vertices.size() * sizeof(glm::vec3), data->vertices.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &data->normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, data->normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, data->normals.size() * sizeof(glm::vec3), data->normals.data(), GL_STATIC_DRAW);
	
;
	tex.loadFromFile("./Resources/IMAGES/SFML-LOGO.png");
	id = tex.getNativeHandle();
}

Mesh::~Mesh()
{
	all.erase(std::remove(all.begin(), all.end(), this), all.end());
}

void Mesh::draw(glm::mat4 const& Perspective, glm::mat4 const& View, GLuint programID) const
{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, data->vertexBuffer);
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
		glBindBuffer(GL_ARRAY_BUFFER, data->normalBuffer);
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

		const GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, data->vertices.size());
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
