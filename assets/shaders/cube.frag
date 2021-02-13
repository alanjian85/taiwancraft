#version 330 core

in vec3 normal;
in vec2 uv;

out vec4 fragColor;

uniform sampler2D dirt;

void main()
{
	fragColor = texture(dirt, uv);
}