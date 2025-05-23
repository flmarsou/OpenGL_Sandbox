#include "config.hpp"

namespace	Input
{
	unsigned int	blockSelected = EMPTY_BLOCK;
	bool			toggleBucket = false;
	bool			togglePause = false;
	bool			toggleVSync = false;

	bool			mouseLeftPressed;
	bool			mouseRightPressed;
	bool			mouseMiddlePressed;
	double			mouseScroll = 0;
	int				cursorSize = 1;
}

static void	framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	(void)window;
	(void)width;

	glViewport(0, 0, height, height);
}

static void	scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	(void)window;
	(void)xOffset;

	Input::mouseScroll = yOffset;
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
				if (!Input::toggleVSync)
					Input::toggleVSync = true;
				else if (Input::toggleVSync)
					Input::toggleVSync = false;
				break ;

			case (GLFW_KEY_SPACE):
				if (!Input::togglePause)
					Input::togglePause = true;
				else if (Input::togglePause)
					Input::togglePause = false;
				break ;

			case (GLFW_KEY_LEFT_SHIFT):
				if (!Input::toggleBucket)
					Input::toggleBucket = true;
				break ;
		}
	}
	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
			case (GLFW_KEY_LEFT_SHIFT):
				if (Input::toggleBucket)
					Input::toggleBucket = false;
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
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		switch (action)
		{
			case (GLFW_PRESS):
				Input::mouseMiddlePressed = true;
				break ;

			case (GLFW_RELEASE):
				Input::mouseMiddlePressed = false;
				break ;
		}
	}
}

void	initCallbacks(GLFWwindow *&window)
{
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}
