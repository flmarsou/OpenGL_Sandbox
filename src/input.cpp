#include "config.hpp"

namespace	Input
{
	unsigned int	blockSelected;
	bool			keyFPSToggle;
	bool			keyVSyncToggle;
	bool			keyPauseToggle;

	bool			mouseLeftPressed;
}

static void	framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
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

			case (GLFW_KEY_F3):
				if (!Input::keyFPSToggle)
				{
					std::cout << INFO "FPS On!" << std::endl;
					Input::keyFPSToggle = true;
				}
				else
				{
					std::cout << INFO "FPS Off!" << std::endl;
					Input::keyFPSToggle = false;
				}
				break ;

			case (GLFW_KEY_F4):
				if (!Input::keyVSyncToggle)
				{
					std::cout << INFO "V-Sync On!" << std::endl;
					glfwSwapInterval(0);
					Input::keyVSyncToggle = true;
				}
				else
				{
					std::cout << INFO "V-Sync Off!" << std::endl;
					glfwSwapInterval(1);
					Input::keyVSyncToggle = false;
				}
				break ;

			case (GLFW_KEY_SPACE):
				if (!Input::keyPauseToggle)
				{
					std::cout << INFO "Paused!" << std::endl;
					Input::keyPauseToggle = true;
				}
				else
				{
					std::cout << INFO "Unpaused!" << std::endl;
					Input::keyPauseToggle = false;
				}
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
}

void	initCallbacks(GLFWwindow *window)
{
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}
