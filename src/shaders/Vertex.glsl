#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 MVP;

out vec3 normal;
out vec2 UV;

void main()
{
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
	normal = vertexNormal;
	UV = vec2(vertexPosition_modelspace.x, 1.0-vertexPosition_modelspace.y);
}