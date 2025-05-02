#include "config.hpp"
#include "Grid.hpp"
#include "SandBlock.hpp"
#include "WaterBlock.hpp"

Grid	*grid = new Grid(GRID_SIZE);
bool	mouseLeftPressed = false;
int		keypadSelected = 1;

static void	keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;
	(void)scancode;
	(void)mods;

	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_1)
			keypadSelected = 1;
		else if (key == GLFW_KEY_2)
			keypadSelected = 2;
	}
}

static void	mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	(void)window;
	(void)mods;

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
			mouseLeftPressed = true;
		else if (action == GLFW_RELEASE)
			mouseLeftPressed = false;
	}
}

int	main()
{
	GLFWwindow		*window;
	unsigned int	shader;

	if (!initGLFW(window) || !initGLAD() || !initShader(shader))
		return (-1);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetKeyCallback(window, keyCallback);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

		grid->draw(shader);
		grid->update();

		if (mouseLeftPressed)
		{
			double	xpos;
			double	ypos;

			glfwGetCursorPos(window, &xpos, &ypos);

			const unsigned int	cellX = static_cast<unsigned int>((xpos / WINDOW_WIDTH) * GRID_SIZE);
			const unsigned int	cellY = static_cast<unsigned int>((ypos / WINDOW_HEIGHT) * GRID_SIZE);

			if (mouseLeftPressed)
			{
				switch (keypadSelected)
				{
					case (1):
						grid->setBlock(cellX, cellY, new SandBlock());
						break ;

					case (2):
						grid->setBlock(cellX, cellY, new WaterBlock());
						break ;
				}
			}
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
