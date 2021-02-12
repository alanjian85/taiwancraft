#version 330 core

in vec3 color;

out vec4 fragColor;

void main()
{
	vec3 temp = color;
	for (int i = 0; i < 3; ++i) {
		if (temp[i] < 0.95f && temp[i] > 0.75f) temp[i] *= 0.8f;
		else if (temp[i] > 0.5f) temp[i] *= 0.6f;
		else if (temp[i] > 0.25f) temp[i] *= 0.4f;
		else if (temp[i] > 0.1f) temp[i] *= 0.2f;
		else temp[i] *= 0.0f;
	}
	fragColor = vec4(temp, 0.0f);
}