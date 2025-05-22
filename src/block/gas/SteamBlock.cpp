#include "SteamBlock.hpp"
#include "WaterBlock.hpp"

SteamBlock::SteamBlock()
{
	setId(STEAM_BLOCK);

	randomizeColor();
}

ABlock	*SteamBlock::clone() const
{
	return (new SteamBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	SteamBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.80f, 0.85f, 0.90f}); break ;
		case (1): setColor({0.70f, 0.78f, 0.85f}); break ;
		case (2): setColor({0.60f, 0.70f, 0.80f}); break ;
		case (3): setColor({0.50f, 0.60f, 0.70f}); break ;
		default: setColor({0.40f, 0.50f, 0.60f}); break ;
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	SteamBlock::update(Grid &grid, const int x, const int y)
{
	// Condensates
	if (std::rand() % 10000 < 5)
	{
		grid.deleteBlock(x, y);
		grid.setBlock(x, y, new WaterBlock());
		return ;
	}

	// Color
	if (std::rand() % 100 == 1)
		randomizeColor();

	// Movements
	if (swapAbove(grid, x, y))
		return ;
	if (blockedMovements(grid, x, y))
		return ;
	if (risingMovements(grid, x, y))
		return ;
}
