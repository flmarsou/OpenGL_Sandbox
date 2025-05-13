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
			case (GLFW_KEY_1):
				Input::keyPressed = GLFW_KEY_1;
				std::cout << INFO "Sand Selected!" << std::endl;
				break ;
			case (GLFW_KEY_2):
				Input::keyPressed = GLFW_KEY_2;
				std::cout << INFO "Water Selected!" << std::endl;
				break ;
			case (GLFW_KEY_3):
				Input::keyPressed = GLFW_KEY_3;
				std::cout << INFO "Stone Selected!" << std::endl;
				break ;
			case (GLFW_KEY_4):
				Input::keyPressed = GLFW_KEY_4;
				std::cout << INFO "Bomb Selected!" << std::endl;
				break ;
			case (GLFW_KEY_5):
				Input::keyPressed = GLFW_KEY_5;
				std::cout << INFO "Fire Selected!" << std::endl;
				break ;
			case (GLFW_KEY_6):
				Input::keyPressed = GLFW_KEY_6;
				std::cout << INFO "Acid Selected!" << std::endl;
				break ;
			case (GLFW_KEY_7):
				Input::keyPressed = GLFW_KEY_7;
				std::cout << INFO "Wood Selected!" << std::endl;
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
