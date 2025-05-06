#include "config.hpp"

Grid	*grid = new Grid(GRID_SIZE);
bool	mouseLeftPressed = false;
int		keypadSelected = 1;
bool	fpsPrintToggle = false;
bool	fpsCapToggle = false;

static void	printFPS()
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
		else if (key == GLFW_KEY_3)
			keypadSelected = 3;
		else if (key == GLFW_KEY_4)
			keypadSelected = 4;

		if (key == GLFW_KEY_F3 && fpsPrintToggle == false)
			fpsPrintToggle = true;
		else if (key == GLFW_KEY_F3 && fpsPrintToggle == true)
			fpsPrintToggle = false;

		if (key == GLFW_KEY_F4 && fpsCapToggle == false)
		{
			std::cout << INFO "V-Sync Off!" << std::endl;
			glfwSwapInterval(0);
			fpsCapToggle = true;
		}
		else if (key == GLFW_KEY_F4 && fpsCapToggle == true)
		{
			std::cout << INFO "V-Sync On!" << std::endl;
			glfwSwapInterval(1);
			fpsCapToggle = false;
		}
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

	ABlock::initBlock();

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

			const int	cellX = static_cast<int>((xpos / WINDOW_WIDTH) * GRID_SIZE);
			const int	cellY = static_cast<int>((ypos / WINDOW_HEIGHT) * GRID_SIZE);

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

					case (3):
						grid->setBlock(cellX, cellY, new StoneBlock());
						grid->setBlock(cellX - 1, cellY, new StoneBlock());
						grid->setBlock(cellX + 1, cellY, new StoneBlock());
						grid->setBlock(cellX, cellY - 1, new StoneBlock());
						grid->setBlock(cellX, cellY + 1, new StoneBlock());
						break ;

					case (4):
						grid->setBlock(cellX, cellY, new BombBlock());
						break ;
				}
			}
		}

		if (fpsPrintToggle)
			printFPS();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ABlock::deleteBlock();
	delete grid;
	glDeleteProgram(shader);
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << INFO "Closing the game..." << std::endl;
	return (0);
}
