#include "config.hpp"
#include "enums.hpp"

static void	drawGui(GLFWwindow *&window)
{
	static int	tempSize = -1;
	int	width;
	int	height;

	glfwGetFramebufferSize(window, &width, &height);

	if (tempSize != width)
	{
		tempSize = width;

		ImGui::SetNextWindowPos(ImVec2((float)height, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float)(width - height), (float)height), ImGuiCond_Always);
	}

	ImGui::Begin("Tool Box", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

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
	ImGui::SliderInt("Cursor", &Input::cursorSize, 1, 10);
	if (ImGui::Button("Toggle V-Sync"))
		toggleVSync();
	if (ImGui::Button("Toggle Pause"))
		togglePause();

	ImGui::Text("FPS: %.f", ImGui::GetIO().Framerate);
}

static void	placeBlock(GLFWwindow *&window, Grid *grid)
{
	double	xpos;
	double	ypos;
	int		width;
	int		height;

	glfwGetCursorPos(window, &xpos, &ypos);
	glfwGetFramebufferSize(window, &width, &height);

	const int	cellX = static_cast<int>((xpos / height) * GRID_SIZE);
	const int	cellY = static_cast<int>((ypos / height) * GRID_SIZE);

	switch (Input::blockSelected)
	{
		case (SAND_BLOCK):
			grid->place(cellX, cellY, new SandBlock(), Input::cursorSize);
			break ;

		case (WATER_BLOCK):
			grid->place(cellX, cellY, new WaterBlock(), Input::cursorSize);
			break ;

		case (STONE_BLOCK):
			grid->place(cellX, cellY, new StoneBlock(), Input::cursorSize);
			break ;

		case (BOMB_BLOCK):
			grid->place(cellX, cellY, new BombBlock(), Input::cursorSize);
			break ;

		case (FIRE_BLOCK):
			grid->place(cellX, cellY, new FireBlock(), Input::cursorSize);
			break ;

		case (ACID_BLOCK):
			grid->place(cellX, cellY, new AcidBlock(), Input::cursorSize);
			break ;

		case (WOOD_BLOCK):
			grid->place(cellX, cellY, new WoodBlock(), Input::cursorSize);
			break ;

		case (ASH_BLOCK):
			grid->place(cellX, cellY, new AshBlock(), Input::cursorSize);
			break ;

		case (TOXIC_SLUDGE_BLOCK):
			grid->place(cellX, cellY, new ToxicSludgeBlock(), Input::cursorSize);
			break ;

		case (FLAMMABLE_GAS_BLOCK):
			grid->place(cellX, cellY, new FlammableGasBlock(), Input::cursorSize);
			break ;

		case (STEAM_BLOCK):
			grid->place(cellX, cellY, new SteamBlock(), Input::cursorSize);
			break ;

		case (MUD_BLOCK):
			grid->place(cellX, cellY, new MudBlock(), Input::cursorSize);
			break ;

		default:
			break ;
	}
}

void	gameLoop(GLFWwindow *&window, const unsigned int &shader, Grid *&grid)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	grid->draw(shader);
	if (!Input::keyPauseToggle)
		grid->update();

	if (Input::mouseLeftPressed && !ImGui::GetIO().WantCaptureMouse)
		placeBlock(window, grid);

	drawGui(window);

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
