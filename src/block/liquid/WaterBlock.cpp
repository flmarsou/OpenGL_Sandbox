#include "WaterBlock.hpp"
#include "SandBlock.hpp"
#include "SteamBlock.hpp"

WaterBlock::WaterBlock()
{
	setId(WATER_BLOCK);
	setType(LIQUID_TYPE);

	randomizeColor();
}

ABlock *WaterBlock::clone() const
{
	return (new WaterBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	WaterBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.102f, 0.518f, 0.722f}); break ;
		case (1): setColor({0.102f, 0.549f, 0.722f}); break ;
		case (2): setColor({0.102f, 0.580f, 0.722f}); break ;
		case (3): setColor({0.102f, 0.611f, 0.722f}); break ;
		default: setColor({0.102f, 0.643f, 0.722f}); break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static bool	boil(Grid &grid, const int x, const int y)
{
	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x, y - 1, new SteamBlock());
		return (true);
	}
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x - 1, y, new SteamBlock());
		return (true);
	}
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x + 1, y, new SteamBlock());
		return (true);
	}
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x, y + 1, new SteamBlock());
		return (true);
	}
	return (false);
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	WaterBlock::update(Grid &grid, const int x, const int y)
{
	// Water to Steam
	if (std::rand() % 10 == 1 && boil(grid, x, y))
	{
		grid.deleteBlock(x, y);
		return ;
	}

	// Color
	if (std::rand() % 100 == 1)
		randomizeColor();

	// Movements
	if (swapAbove(grid, x, y))
		return ;
	if (groundMovements(grid, x, y))
		return ;
	if (fallDown(grid, x, y))
		return ;
	if (diagonalMovements(grid, x, y))
		return ;

	// Stone to Sand
	if (std::rand() % 1000 == 0 && grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == STONE_BLOCK)
		grid.convertBlock(x, y + 1, new SandBlock());
}
