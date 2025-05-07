#include "config.hpp"

static void	placeBlock(GLFWwindow *window, Grid *grid)
{
	double	xpos;
	double	ypos;

	glfwGetCursorPos(window, &xpos, &ypos);

	const int	cellX = static_cast<int>((xpos / WINDOW_WIDTH) * GRID_SIZE);
	const int	cellY = static_cast<int>((ypos / WINDOW_HEIGHT) * GRID_SIZE);

	switch (Input::keyPressed)
	{
		case (GLFW_KEY_1):
			grid->setBlock(cellX, cellY, new SandBlock());
			break ;

		case (GLFW_KEY_2):
			grid->setBlock(cellX, cellY, new WaterBlock());
			break ;

		case (GLFW_KEY_3):
			grid->setBlock(cellX, cellY, new StoneBlock());
			grid->setBlock(cellX - 1, cellY, new StoneBlock());
			grid->setBlock(cellX + 1, cellY, new StoneBlock());
			grid->setBlock(cellX, cellY - 1, new StoneBlock());
			grid->setBlock(cellX, cellY + 1, new StoneBlock());
			break ;

		case (GLFW_KEY_4):
			grid->setBlock(cellX, cellY, new BombBlock());
			break ;

		case (GLFW_KEY_5):
			grid->setBlock(cellX, cellY, new AcidBlock());
			break ;
	}
}

void	gameLoop(GLFWwindow *window, const unsigned int &shader, Grid *grid)
{
	grid->draw(shader);
	grid->update();

	if (Input::mouseLeftPressed)
		placeBlock(window, grid);

	if (Input::keyFPSToggle)
		printFPS();
}
