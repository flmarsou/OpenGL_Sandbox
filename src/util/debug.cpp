# include "config.hpp"

void	togglePause()
{
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
}

void	toggleVSync()
{
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
}
