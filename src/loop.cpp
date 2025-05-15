#include "config.hpp"
#include "enums.hpp"

static void	drawGui()
{
	ImGui::Begin("Tool Box");

	if (ImGui::CollapsingHeader("Solids:"))
	{
		if (ImGui::Button("Stone"))
			Input::blockSelected = STONE_BLOCK;
		if (ImGui::Button("Wood"))
			Input::blockSelected = WOOD_BLOCK;
	}
	if (ImGui::CollapsingHeader("Powders:"))
	{
		if (ImGui::Button("Sand"))
			Input::blockSelected = SAND_BLOCK;
		if (ImGui::Button("Ash"))
			Input::blockSelected = ASH_BLOCK;
		if (ImGui::Button("Mud"))
			Input::blockSelected = MUD_BLOCK;
	}
	if (ImGui::CollapsingHeader("Liquids:"))
	{
		if (ImGui::Button("Water"))
			Input::blockSelected = WATER_BLOCK;
		if (ImGui::Button("Acid"))
			Input::blockSelected = ACID_BLOCK;
		if (ImGui::Button("Toxic Sludge"))
			Input::blockSelected = TOXIC_SLUDGE_BLOCK;
	}
	if (ImGui::CollapsingHeader("Gasses:"))
	{
		if (ImGui::Button("Steam"))
			Input::blockSelected = STEAM_BLOCK;
		if (ImGui::Button("Flammable Gas"))
			Input::blockSelected = FLAMMABLE_GAS_BLOCK;
	}
	if (ImGui::CollapsingHeader("Reactives:"))
	{
		if (ImGui::Button("Fire"))
			Input::blockSelected = FIRE_BLOCK;
		if (ImGui::Button("Bomb"))
			Input::blockSelected = BOMB_BLOCK;
	}
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
		case (SAND_BLOCK):
			grid->setBlock(cellX, cellY, new SandBlock());
			break ;

		case (WATER_BLOCK):
			grid->setBlock(cellX, cellY, new WaterBlock());
			break ;

		case (STONE_BLOCK):
			grid->setBlock(cellX, cellY, new StoneBlock());
			break ;

		case (BOMB_BLOCK):
			grid->setBlock(cellX, cellY, new BombBlock());
			break ;

		case (FIRE_BLOCK):
			grid->setBlock(cellX, cellY, new FireBlock());
			break ;

		case (ACID_BLOCK):
			grid->setBlock(cellX, cellY, new AcidBlock());
			break ;

		case (WOOD_BLOCK):
			grid->setBlock(cellX, cellY, new WoodBlock());
			break ;

		case (ASH_BLOCK):
			grid->setBlock(cellX, cellY, new AshBlock());
			break ;

		case (TOXIC_SLUDGE_BLOCK):
			grid->setBlock(cellX, cellY, new ToxicSludgeBlock());
			break ;

		case (FLAMMABLE_GAS_BLOCK):
			grid->setBlock(cellX, cellY, new FlammableGasBlock());
			break ;

		case (STEAM_BLOCK):
			grid->setBlock(cellX, cellY, new SteamBlock());
			break ;

		case (MUD_BLOCK):
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

	if (Input::keyFPSToggle)
		printFPS();

	if (Input::mouseLeftPressed && !ImGui::GetIO().WantCaptureMouse)
		placeBlock(window, grid);

	drawGui();

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
