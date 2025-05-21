# include "config.hpp"

void	togglePause()
{
	if (!Input::togglePause)
	{
		std::cout << INFO "Paused!" << std::endl;
		Input::togglePause = true;
	}
	else
	{
		std::cout << INFO "Unpaused!" << std::endl;
		Input::togglePause = false;
	}
}

void	toggleVSync()
{
	if (!Input::toggleVSync)
	{
		std::cout << INFO "V-Sync On!" << std::endl;
		glfwSwapInterval(0);
		Input::toggleVSync = true;
	}
	else
	{
		std::cout << INFO "V-Sync Off!" << std::endl;
		glfwSwapInterval(1);
		Input::toggleVSync = false;
	}
}
