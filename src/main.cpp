#include "config.hpp"

static void	terminateProgram(Grid *&grid, unsigned int &shader, GLFWwindow *&window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	ABlock::deleteBlock();

	delete grid;

	glDeleteProgram(shader);

	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << INFO "Closing the game..." << std::endl;
}

int	main()
{
	GLFWwindow		*window;
	unsigned int	shader;

	if (!initGLFW(window) || !initGLAD() || !initShader(shader))
		return (-1);
	initCallbacks(window);
	initImGui(window);

	Grid	*grid = new Grid(GRID_SIZE);
	ABlock::initBlock();

	glViewport(0, 0, WINDOW_HEIGHT, WINDOW_HEIGHT);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

		gameLoop(window, shader, grid);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	terminateProgram(grid, shader, window);
	return (0);
}
