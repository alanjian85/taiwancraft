#version 330 core

in vec3 normal;
in vec2 uv;

out vec4 fragColor;

void main()
{
	fragColor = vec4((normal + 1.0f) / 2.0f, 0.0f);
}