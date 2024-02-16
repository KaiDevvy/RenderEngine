#include "RenderEngine.h"

#include <iostream>
#include <GL/glew.h>
#include "GLShaderLoad.hpp"
#include "Mesh.h"

RenderEngine::RenderEngine()
{
	glewInit();
	
	programID = LoadShaders("Vertex.glsl", "Fragment.glsl");
	
}

void RenderEngine::setPerspective(float FOV, float aspectRatio, float nearDist, float farDist)
{
	projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDist, farDist);
}

void RenderEngine::setView(glm::mat4 const& newView)
{
	view = newView;
}


void RenderEngine::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programID);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Render all meshes
	for (Mesh const* mesh : Mesh::all)
	{
		mesh->draw(projection, view, programID);
	}
}
