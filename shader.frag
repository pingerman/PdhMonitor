#version 330

in  vec3 outColor;
out vec4 resultColor;

void main(void)
{
	resultColor = vec4(outColor,1.0);
}