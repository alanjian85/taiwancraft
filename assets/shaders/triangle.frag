#version 330 core

in vec3 color;

out vec4 fragColor;

void main()
{
	vec3 temp = color;
	temp.r = floor(temp.r * pow(2, 3)) / pow(2, 3);
	temp.r = floor(temp.r * pow(2, 3)) / pow(2, 3);
	temp.r = floor(temp.r * pow(2, 2)) / pow(2, 2);
	fragColor = vec4(temp, 0.0f);
}