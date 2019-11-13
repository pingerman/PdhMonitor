#version 330

#define VERT_OFFSET 0

layout(location = VERT_OFFSET) in vec3 vertex;

uniform vec3 color;

out vec3 outColor;

void main(void)
{
	gl_Position = vec4(vertex.xyz, 1.0);
	outColor = color.xyz; 
}