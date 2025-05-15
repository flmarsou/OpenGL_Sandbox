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

void	toggleFPS()
{
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
}

void	printFPS()
{
	static int												frameCount = 0;
	static std::chrono::high_resolution_clock::time_point	lastTime = std::chrono::high_resolution_clock::now();

	const std::chrono::high_resolution_clock::time_point	currentTime = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double>						elapsed = currentTime - lastTime;

	frameCount++;

	if (elapsed.count() >= 1.0)
	{
		std::cout << "FPS: " << frameCount << std::endl;
		frameCount = 0;
		lastTime = currentTime;
	}
}
