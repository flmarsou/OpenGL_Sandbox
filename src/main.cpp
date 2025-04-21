#include "config.h"

static bool	initGLFW(GLFWwindow *&window)
{
	// GLFW: Initializes and configures
	if (!glfwInit())
	{
		std::cerr << ERROR "Failed to initialize GLFW!" << std::endl;
		return (false);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW: Window creation
	window = glfwCreateWindow(640, 480, "OpenGL Sandbox", NULL, NULL);
	if (!window)
	{
		std::cerr << ERROR "Failed to create the window!" << std::endl;
		glfwTerminate();
		return (false);
	}

	glfwMakeContextCurrent(window);
	return (true);
}

static bool	initGLAD()
{
	// GLAD: Loads OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << ERROR "Failed to initialize GLAD!" << std::endl;
		glfwTerminate();
		return (true);
	}
	return (true);
}

int	main()
{
	GLFWwindow	*window;

	if (!initGLFW(window) || !initGLAD())
		return (-1);

	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

	unsigned int	vertexShader = makeModule("../shaders/vertex.glsl", GL_VERTEX_SHADER);
	unsigned int	fragmentShader = makeModule("../shaders/fragment.glsl", GL_FRAGMENT_SHADER);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return (0);
}
