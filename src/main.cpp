#include "config.hpp"
#include "Grid.hpp"
#include "SandBlock.hpp"

Grid	*grid = new Grid();

static void	mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	(void)mods;

	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
	{
		double	xpos;
		double	ypos;

		glfwGetCursorPos(window, &xpos, &ypos);

		ypos = WINDOW_HEIGHT - ypos;

		const unsigned int	cellX = static_cast<unsigned int>((xpos / WINDOW_WIDTH) * 100);
		const unsigned int	cellY = static_cast<unsigned int>((ypos / WINDOW_HEIGHT) * 100);

		grid->setBlock(cellX, cellY, new SandBlock());
	}
}

int	main()
{
	GLFWwindow		*window;
	unsigned int	shader;

	if (!initGLFW(window) || !initGLAD())
		return (-1);

	shader = initShader();
	glUseProgram(shader);

	while (!glfwWindowShouldClose(window))
	{
		// Input/Events (keyboard, mouse, etc...)
		glfwPollEvents();
		glfwSetMouseButtonCallback(window, mouseButtonCallback);

		// Window rendering
		glClear(GL_COLOR_BUFFER_BIT);
		grid->renderGrid();
		glfwSwapBuffers(window);
	}

	delete (grid);
	glDeleteProgram(shader);
	glfwTerminate();
	std::cout << INFO "Closing the game..." << std::endl;
	return (0);
}
