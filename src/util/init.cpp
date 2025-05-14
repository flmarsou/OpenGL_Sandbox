#include "config.hpp"

bool	initGLFW(GLFWwindow *&window)
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
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	std::cout << SUCCESS "GLFW initialized successfully!" << std::endl;

	// GLFW: Window creation
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		std::cerr << ERROR "Failed to create the window!" << std::endl;
		glfwTerminate();
		return (false);
	}
	glfwSetWindowAspectRatio(window, 1, 1);
	glfwMakeContextCurrent(window);
	std::cout << SUCCESS "Window created successfully!" << std::endl;

	return (true);
}

bool	initGLAD()
{
	// GLAD: Loads OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << ERROR "Failed to initialize GLAD!" << std::endl;
		glfwTerminate();
		return (true);
	}
	std::cout << SUCCESS "GLAD initialized successfully!" << std::endl;

	return (true);
}
