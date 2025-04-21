#version 460 core

int vec3	vColor;

out vec4	fragmentColor;

void	main()
{
	fragmentColor = vec4(vColor, 1.0);
}
