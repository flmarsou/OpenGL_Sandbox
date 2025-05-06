#include "config.hpp"

Grid	*grid = new Grid(GRID_SIZE);

int	main()
{
	GLFWwindow		*window;
	unsigned int	shader;

	if (!initGLFW(window) || !initGLAD() || !initShader(shader))
		return (-1);
	initCallbacks(window);

	ABlock::initBlock();

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

		gameLoop(window, shader, grid);

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
