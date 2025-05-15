#include "config.hpp"

namespace	Input
{
	unsigned int	blockSelected = EMPTY_BLOCK;
	bool			keyVSyncToggle = false;
	bool			keyPauseToggle = false;

	bool			mouseLeftPressed;
	bool			mouseRightPressed;
	int				cursorSize = 1;
}

static void	framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	(void)window;
	(void)width;

	glViewport(0, 0, height, height);
}

static void	keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;
	(void)scancode;
	(void)mods;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case (GLFW_KEY_ESCAPE):
				glfwSetWindowShouldClose(window, true);
				break ;

			case (GLFW_KEY_F4):
				toggleVSync();
				break ;

			case (GLFW_KEY_SPACE):
				togglePause();
				break ;
		}
	}
}

static void	mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	(void)window;
	(void)mods;

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		switch (action)
		{
			case (GLFW_PRESS):
				Input::mouseLeftPressed = true;
				break ;

			case (GLFW_RELEASE):
				Input::mouseLeftPressed = false;
				break ;
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		switch (action)
		{
			case (GLFW_PRESS):
				Input::mouseRightPressed = true;
				break ;

			case (GLFW_RELEASE):
				Input::mouseRightPressed = false;
				break ;
		}
	}
}

void	initCallbacks(GLFWwindow *&window)
{
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}
