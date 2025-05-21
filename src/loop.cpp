#include "config.hpp"
#include "enums.hpp"

#include "SandBlock.hpp"
#include "WaterBlock.hpp"
#include "StoneBlock.hpp"
#include "BombBlock.hpp"
#include "FireBlock.hpp"
#include "AcidBlock.hpp"
#include "WoodBlock.hpp"
#include "AshBlock.hpp"
#include "ToxicSludgeBlock.hpp"
#include "FlammableGasBlock.hpp"
#include "SteamBlock.hpp"
#include "MudBlock.hpp"
#include "BatteryBlock.hpp"
#include "MetalBlock.hpp"
#include "RedLedBlock.hpp"
#include "GreenLedBlock.hpp"
#include "BlueLedBlock.hpp"
#include "C4Block.hpp"

static void	drawGui(GLFWwindow *window)
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
		if (ImGui::Button("Metal"))
			Input::blockSelected = METAL_BLOCK;
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

	if (ImGui::CollapsingHeader("Electricity:"))
	{
		if (ImGui::Button("Battery"))
			Input::blockSelected = BATTERY_BLOCK;
		if (ImGui::Button("Red LED"))
			Input::blockSelected = RED_LED_BLOCK;
		if (ImGui::Button("Green LED"))
			Input::blockSelected = GREEN_LED_BLOCK;
		if (ImGui::Button("Blue LED"))
			Input::blockSelected = BLUE_LED_BLOCK;
		if (ImGui::Button("C4"))
			Input::blockSelected = C4_BLOCK;
	}

	ImGui::SliderInt("Cursor", &Input::cursorSize, 1, 10);

	ImGui::Checkbox("Bucket", &Input::toggleBucket);
	ImGui::Checkbox("Pause", &Input::togglePause);
	ImGui::Checkbox("V-Sync", &Input::toggleVSync);

	ImGui::Text("FPS: %.f", ImGui::GetIO().Framerate);
}

static void	getCursorPos(GLFWwindow *window, int &x, int &y)
{
	double	xpos;
	double	ypos;
	int		width;
	int		height;

	glfwGetCursorPos(window, &xpos, &ypos);
	glfwGetFramebufferSize(window, &width, &height);

	x = static_cast<int>((xpos / height) * GRID_SIZE);
	y = static_cast<int>((ypos / height) * GRID_SIZE);
}

static void	placeBlock(GLFWwindow *window, Grid *&grid)
{
	int	x;
	int	y;

	getCursorPos(window, x, y);

	switch (Input::blockSelected)
	{
		case (SAND_BLOCK): grid->place(x, y, new SandBlock(), Input::cursorSize); break ;
		case (WATER_BLOCK): grid->place(x, y, new WaterBlock(), Input::cursorSize); break ;
		case (STONE_BLOCK): grid->place(x, y, new StoneBlock(), Input::cursorSize); break ;
		case (BOMB_BLOCK): grid->place(x, y, new BombBlock(), Input::cursorSize); break ;
		case (FIRE_BLOCK): grid->place(x, y, new FireBlock(), Input::cursorSize); break ;
		case (ACID_BLOCK): grid->place(x, y, new AcidBlock(), Input::cursorSize); break ;
		case (WOOD_BLOCK): grid->place(x, y, new WoodBlock(), Input::cursorSize); break ;
		case (ASH_BLOCK): grid->place(x, y, new AshBlock(), Input::cursorSize); break ;
		case (TOXIC_SLUDGE_BLOCK): grid->place(x, y, new ToxicSludgeBlock(), Input::cursorSize); break ;
		case (FLAMMABLE_GAS_BLOCK): grid->place(x, y, new FlammableGasBlock(), Input::cursorSize); break ;
		case (STEAM_BLOCK): grid->place(x, y, new SteamBlock(), Input::cursorSize); break ;
		case (MUD_BLOCK): grid->place(x, y, new MudBlock(), Input::cursorSize); break ;
		case (BATTERY_BLOCK): grid->place(x, y, new BatteryBlock(), Input::cursorSize); break ;
		case (METAL_BLOCK): grid->place(x, y, new MetalBlock(), Input::cursorSize); break ;
		case (RED_LED_BLOCK): grid->place(x, y, new RedLedBlock(), Input::cursorSize); break ;
		case (GREEN_LED_BLOCK): grid->place(x, y, new GreenLedBlock(), Input::cursorSize); break ;
		case (BLUE_LED_BLOCK): grid->place(x, y, new BlueLedBlock(), Input::cursorSize); break ;
		case (C4_BLOCK): grid->place(x, y, new C4Block(), Input::cursorSize); break ;

		default: break ;
	}
}

static void	floodFillPlaceBucket(Grid *&grid, const int x, const int y, ABlock *&block)
{
	if (x < 0 || x >= grid->getSize() || y < 0 || y >= grid->getSize() || grid->getBlock(x, y))
		return ;

	ABlock	*newBlock = block->clone();

	grid->setBlock(x, y, newBlock);

	floodFillPlaceBucket(grid, x, y + 1, newBlock);
	floodFillPlaceBucket(grid, x - 1, y, newBlock);
	floodFillPlaceBucket(grid, x + 1, y, newBlock);
	floodFillPlaceBucket(grid, x, y - 1, newBlock);
}

static void	placeBlockBucket(GLFWwindow *window, Grid *&grid)
{
	int	x;
	int	y;

	getCursorPos(window, x, y);

	ABlock	*tempBlock;

	switch (Input::blockSelected)
	{
		case (SAND_BLOCK): tempBlock = new SandBlock(); break ;
		case (WATER_BLOCK): tempBlock = new WaterBlock(); break ;
		case (STONE_BLOCK): tempBlock = new StoneBlock(); break ;
		case (BOMB_BLOCK): tempBlock = new BombBlock(); break ;
		case (FIRE_BLOCK): tempBlock = new FireBlock(); break ;
		case (ACID_BLOCK): tempBlock = new AcidBlock(); break ;
		case (WOOD_BLOCK): tempBlock = new WoodBlock(); break ;
		case (ASH_BLOCK): tempBlock = new AshBlock(); break ;
		case (TOXIC_SLUDGE_BLOCK): tempBlock = new ToxicSludgeBlock(); break ;
		case (FLAMMABLE_GAS_BLOCK): tempBlock = new FlammableGasBlock(); break ;
		case (STEAM_BLOCK): tempBlock = new SteamBlock(); break ;
		case (MUD_BLOCK): tempBlock = new MudBlock(); break ;
		case (BATTERY_BLOCK): tempBlock = new BatteryBlock(); break ;
		case (METAL_BLOCK): tempBlock = new MetalBlock(); break ;
		case (RED_LED_BLOCK): tempBlock = new RedLedBlock(); break ;
		case (GREEN_LED_BLOCK): tempBlock = new GreenLedBlock(); break ;
		case (BLUE_LED_BLOCK): tempBlock = new BlueLedBlock(); break ;
		case (C4_BLOCK): tempBlock = new C4Block(); break ;

		default: return ;
	}

	floodFillPlaceBucket(grid, x, y, tempBlock);
	delete tempBlock;
}

static void	eraseBlock(GLFWwindow *window, Grid *&grid)
{
	int	x;
	int	y;

	getCursorPos(window, x, y);

	grid->erase(x, y, Input::cursorSize);
}

static void	floodFillEraseBucket(Grid *&grid, const int x, const int y, const unsigned int block)
{
	if (x < 0 || x >= grid->getSize() || y < 0 || y >= grid->getSize() || !grid->getBlock(x, y) || (grid->getBlock(x, y) && grid->getBlock(x, y)->getId() != block))
		return ;

	grid->deleteBlock(x, y);

	floodFillEraseBucket(grid, x, y + 1, block);
	floodFillEraseBucket(grid, x - 1, y, block);
	floodFillEraseBucket(grid, x + 1, y, block);
	floodFillEraseBucket(grid, x, y - 1, block);
}

static void	eraseBlockBucket(GLFWwindow *window, Grid *&grid)
{
	int	x;
	int	y;

	getCursorPos(window, x, y);

	if (grid->getBlock(x, y))
		floodFillEraseBucket(grid, x, y, grid->getBlock(x, y)->getId());
}

static void	selectBlock(GLFWwindow *window, Grid *&grid)
{
	int	x;
	int	y;

	getCursorPos(window, x, y);

	if (grid->getBlock(x, y))
		Input::blockSelected = grid->getBlock(x, y)->getId();
}

void	gameLoop(GLFWwindow *&window, const unsigned int shader, Grid *&grid)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	grid->draw(shader);

	if (!Input::togglePause)
		grid->update();

	if (!Input::toggleVSync)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	if (Input::mouseLeftPressed && !Input::toggleBucket && !ImGui::GetIO().WantCaptureMouse)
		placeBlock(window, grid);
	else if (Input::mouseLeftPressed && Input::toggleBucket && !ImGui::GetIO().WantCaptureMouse)
		placeBlockBucket(window, grid);
	else if (Input::mouseRightPressed && !Input::toggleBucket && !ImGui::GetIO().WantCaptureMouse)
		eraseBlock(window, grid);
	else if (Input::mouseRightPressed && Input::toggleBucket && !ImGui::GetIO().WantCaptureMouse)
		eraseBlockBucket(window, grid);
	else if (Input::mouseMiddlePressed && !ImGui::GetIO().WantCaptureMouse)
		selectBlock(window, grid);

	drawGui(window);

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
