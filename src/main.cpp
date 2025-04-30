#include "config.hpp"
#include "Grid.hpp"

Grid	*grid = new Grid(GRID_SIZE);

static void	mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	(void)mods;

	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
	{
		double	xpos;
		double	ypos;

		glfwGetCursorPos(window, &xpos, &ypos);

		const unsigned int	cellX = static_cast<unsigned int>((xpos / WINDOW_WIDTH) * GRID_SIZE);
		const unsigned int	cellY = static_cast<unsigned int>((ypos / WINDOW_HEIGHT) * GRID_SIZE);

		grid->setBlock(cellX, cellY, new Block());
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
