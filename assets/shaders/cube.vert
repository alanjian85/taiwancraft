#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUv;

out vec3 normal;
out vec2 uv;

uniform mat4 cameraMatrix, modelMatrix;

void main()
{
	gl_Position = cameraMatrix * modelMatrix * vec4(aPos, 1.0f);
	normal = aNormal;
	uv = aUv;
}