#include "SteamBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

SteamBlock::SteamBlock()
{
	setId(STEAM_BLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	SteamBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.80f, 0.85f, 0.90f});	// Very Light Bluish Gray
			break ;
		case (1):
			setColor({0.70f, 0.78f, 0.85f});	// Light Bluish Gray
			break ;
		case (2):
			setColor({0.60f, 0.70f, 0.80f});	// Bluish Gray
			break ;
		case (3):
			setColor({0.50f, 0.60f, 0.70f});	// Dark Bluish Gray
			break ;
		default:
			setColor({0.40f, 0.50f, 0.60f});	// Very Dark Bluish Gray
			break ;
	}
}

void	SteamBlock::update(Grid &grid, const int x, const int y)
{
	// Condensate
	if (std::rand() % 10000 < 5)
	{
		grid.deleteBlock(x, y);
		grid.setBlock(x, y, new WaterBlock());
		return ;
	}

	// Color
	if (std::rand() % 100 == 1)
		randomizeColor();

	// Swap Above
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == WATER_BLOCK)
	{
		grid.swapBlock(x, y - 1, this, x, y);
		setUpdate(true);
		grid.getBlock(x, y - 1)->setUpdate(true);
		return ;
	}

	// Security & Movement
	if (grid.getBlock(x, y - 1) || y == 0)
	{
		if (std::rand() % 2)
		{
			if (moveLeft(grid, x, y))
				return ;
			if (moveRight(grid, x, y))
				return ;
		}
		else
		{
			if (moveRight(grid, x, y))
				return ;
			if (moveLeft(grid, x, y))
				return ;
		}
	}

	// Rising Movements
	const unsigned int	chance = std::rand() % 10;

	if (chance < 8 && riseUp(grid, x, y))
		return ;
	else if (chance == 8 && riseLeft(grid, x, y))
		return ;
	else if (riseRight(grid, x, y))
		return ;
}
