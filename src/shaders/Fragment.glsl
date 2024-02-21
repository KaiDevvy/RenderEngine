#version 330 core
out vec3 color;
in vec3 normal;
in vec2 UV;

uniform sampler2D myTextureSampler;

void main(){

	float dotProd = dot(normal, vec3(-0.57,0.72,0.38));
	color = vec3(0.7,0.6,0.4);
	
	if (dotProd < 0.75)
		color = color * 0.8;
	if (dotProd < 0.5)
		color = color * 0.8;
	if (dotProd < 0.25)
		color = color * 0.8;


}