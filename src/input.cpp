#include "config.hpp"

namespace	Input
{
	int		keyPressed;
	bool	keyFPSToggle;
	bool	keyVSyncToggle;

	bool	mouseLeftPressed;
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
			// Block Selection
			case (GLFW_KEY_1):
				Input::keyPressed = GLFW_KEY_1;
				break;

			case (GLFW_KEY_2):
				Input::keyPressed = GLFW_KEY_2;
				break ;

			case (GLFW_KEY_3):
				Input::keyPressed = GLFW_KEY_3;
				break ;

			case (GLFW_KEY_4):
				Input::keyPressed = GLFW_KEY_4;
				break ;

			case (GLFW_KEY_5):
				Input::keyPressed = GLFW_KEY_5;
				break ;

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
}
