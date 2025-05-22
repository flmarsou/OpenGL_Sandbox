#include "LavaBlock.hpp"
#include "FireBlock.hpp"
#include "StoneBlock.hpp"

LavaBlock::LavaBlock()
{
	setId(LAVA_BLOCK);
	setType(LIQUID_TYPE);

	randomizeColor();
}

ABlock *LavaBlock::clone() const
{
	return (new LavaBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	LavaBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({1.0f, 0.3f, 0.0f}); break ;
		case (1): setColor({0.9f, 0.2f, 0.0f}); break ;
		case (2): setColor({1.0f, 0.4f, 0.0f}); break ;
		case (3): setColor({0.8f, 0.1f, 0.0f}); break ;
		default: setColor({1.0f, 0.6f, 0.0f}); break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static bool		checkWater(Grid &grid, const int x, const int y)
{
	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == WATER_BLOCK)
	{
		grid.convertBlock(x, y - 1, new StoneBlock());
		return (true);
	}
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == WATER_BLOCK)
	{
		grid.convertBlock(x - 1, y, new StoneBlock());
		return (true);
	}
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == WATER_BLOCK)
	{
		grid.convertBlock(x + 1, y, new StoneBlock());
		return (true);
	}
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == WATER_BLOCK)
	{
		grid.convertBlock(x, y + 1, new StoneBlock());
		return (true);
	}
	return (false);
}

static void	spreadFire(Grid &grid, const int x, const int y)
{
	if (std::rand() % 100 == 1)
	{
		grid.setBlock(x, y - 1, new FireBlock());
		grid.setBlock(x - 1, y - 1, new FireBlock());
		grid.setBlock(x + 1, y - 1, new FireBlock());
		grid.setBlock(x - 1, y, new FireBlock());
		grid.setBlock(x + 1, y, new FireBlock());
		grid.setBlock(x, y + 1, new FireBlock());
		grid.setBlock(x - 1, y + 1, new FireBlock());
		grid.setBlock(x + 1, y + 1, new FireBlock());
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	LavaBlock::update(Grid &grid, const int x, const int y)
{
	if (checkWater(grid, x, y))
		return ;

	spreadFire(grid, x, y);

	// Color
	if (std::rand() % 200 == 1)
		randomizeColor();

	// Movements
	bool	shouldMove = false;

	if (std::rand() % 5 == 1)
		shouldMove = true;

	if (shouldMove && swapAbove(grid, x, y))
		return ;
	if (fallDown(grid, x, y))
		return ;
	if (shouldMove && groundMovements(grid, x, y))
		return ;
	if (shouldMove && diagonalMovements(grid, x, y))
		return ;
}
