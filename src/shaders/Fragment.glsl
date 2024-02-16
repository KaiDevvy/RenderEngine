#version 330 core
out vec3 color;
in vec3 normal;
void main(){

	float dotProd = dot(normal, vec3(0,0.5,0.5));
	color = vec3(dotProd);
}