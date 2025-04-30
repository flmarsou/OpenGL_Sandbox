#include "config.hpp"
#include "Grid.hpp"
#include "SandBlock.hpp"
#include "WaterBlock.hpp"

Grid	*grid = new Grid(GRID_SIZE);
bool	mouseLeftPressed = false;
bool	mouseRightPressed = false;

static void	mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	(void)mods;
	(void)window;

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
			mouseLeftPressed = true;
		else if (action == GLFW_RELEASE)
			mouseLeftPressed = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
			mouseRightPressed = true;
		else if (action == GLFW_RELEASE)
			mouseRightPressed = false;
	}

}

int	main()
{
	GLFWwindow		*window;
	unsigned int	shader;

	if (!initGLFW(window) || !initGLAD() || !initShader(shader))
		return (-1);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

		grid->draw(shader);
		grid->update();

		if (mouseLeftPressed || mouseRightPressed)
		{
			double	xpos;
			double	ypos;

			glfwGetCursorPos(window, &xpos, &ypos);

			const unsigned int	cellX = static_cast<unsigned int>((xpos / WINDOW_WIDTH) * GRID_SIZE);
			const unsigned int	cellY = static_cast<unsigned int>((ypos / WINDOW_HEIGHT) * GRID_SIZE);

			if (mouseLeftPressed)
				grid->setBlock(cellX, cellY, new SandBlock());
			else if (mouseRightPressed)
				grid->setBlock(cellX, cellY, new WaterBlock());
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete grid;
	glDeleteProgram(shader);
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << INFO "Closing the game..." << std::endl;
	return (0);
}
