#version 460 core

layout (location = 0) in vec2	aPos;
layout (location = 1) in mat4	transform;
layout (location = 5) in vec3	instanceColor;

out vec3	vColor;

void main()
{
	gl_Position = transform * vec4(aPos, 0.0, 1.0);
	vColor = instanceColor;
}
