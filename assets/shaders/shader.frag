#version 330 core

in vec2 uv;

out vec4 fragColor;

uniform sampler2D diffuse1;

void main()
{
	fragColor = texture(diffuse1, uv);
}