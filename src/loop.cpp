#include "config.hpp"

static void	drawGui()
{
	ImGui::Begin("Tool Box");

	if (ImGui::Button("Sand"))
		Input::blockSelected = 1;
	else if (ImGui::Button("Water"))
		Input::blockSelected = 2;
	else if (ImGui::Button("Stone"))
		Input::blockSelected = 3;
	else if (ImGui::Button("Bomb"))
		Input::blockSelected = 4;
	else if (ImGui::Button("Fire"))
		Input::blockSelected = 5;
	else if (ImGui::Button("Acid"))
		Input::blockSelected = 6;
	else if (ImGui::Button("Wood"))
		Input::blockSelected = 7;
	else if (ImGui::Button("Mud"))
		Input::blockSelected = 8;

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

static void	placeBlock(GLFWwindow *window, Grid *grid)
{
	double	xpos;
	double	ypos;
	int		width;
	int		height;

	glfwGetCursorPos(window, &xpos, &ypos);
	glfwGetFramebufferSize(window, &width, &height);

	const int	cellX = static_cast<int>((xpos / width) * GRID_SIZE);
	const int	cellY = static_cast<int>((ypos / height) * GRID_SIZE);

	switch (Input::blockSelected)
	{
		case (1):
			grid->setBlock(cellX, cellY, new SandBlock());
			break ;

		case (2):
			grid->setBlock(cellX, cellY, new WaterBlock());
			break ;

		case (3):
			grid->setBlock(cellX, cellY, new StoneBlock());
			break ;

		case (4):
			grid->setBlock(cellX, cellY, new BombBlock());
			break ;

		case (5):
			grid->setBlock(cellX, cellY, new FireBlock());
			break ;

		case (6):
			grid->setBlock(cellX, cellY, new AcidBlock());
			break ;

		case (7):
			grid->setBlock(cellX, cellY, new WoodBlock());
			break ;

		case (8):
			grid->setBlock(cellX, cellY, new MudBlock());
			break ;

		default:
			break ;
	}
}

void	gameLoop(GLFWwindow *window, const unsigned int &shader, Grid *grid)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	grid->draw(shader);
	if (!Input::keyPauseToggle)
		grid->update();

	if (Input::mouseLeftPressed)
		placeBlock(window, grid);

	drawGui();
}
