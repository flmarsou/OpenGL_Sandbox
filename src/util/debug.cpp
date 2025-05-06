# include "config.hpp"

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
