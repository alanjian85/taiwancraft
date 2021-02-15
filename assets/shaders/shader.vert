#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;

out vec2 uv;

uniform mat4 viewMatrix, projectionMatrix;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * vec4(aPos, 1.0f);
	uv = aUV;
}