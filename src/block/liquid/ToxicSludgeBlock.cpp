#include "ToxicSludgeBlock.hpp"
#include "FlammableGasBlock.hpp"

ToxicSludgeBlock::ToxicSludgeBlock()
{
	setId(TOXIC_SLUDGE_BLOCK);
	setType(LIQUID_TYPE);

	randomizeColor();
}

ABlock	*ToxicSludgeBlock::clone() const
{
	return (new ToxicSludgeBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	ToxicSludgeBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.525f, 0.525f, 0.102f}); break ;
		case (1): setColor({0.604f, 0.651f, 0.118f}); break ;
		case (2): setColor({0.451f, 0.576f, 0.094f}); break ;
		case (3): setColor({0.400f, 0.502f, 0.078f}); break ;
		default: setColor({0.380f, 0.455f, 0.078f}); break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static void	convertWater(Grid &grid, const int x, const int y)
{
	// Skip chance
	if (std::rand() % 100 < 90)
		return ;

	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == WATER_BLOCK)
		grid.convertBlock(x, y - 1, new ToxicSludgeBlock());
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == WATER_BLOCK)
		grid.convertBlock(x - 1, y, new ToxicSludgeBlock());
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == WATER_BLOCK)
		grid.convertBlock(x + 1, y, new ToxicSludgeBlock());
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == WATER_BLOCK)
		grid.convertBlock(x, y + 1, new ToxicSludgeBlock());
}

static bool	evaporate(Grid &grid, const int x, const int y)
{
	// Skip chance
	if (std::rand() % 1000 >= 5)
		return (false);

	if (!grid.getBlock(x, y - 1))
	{
		grid.setBlock(x, y - 1, new FlammableGasBlock());
		return (true);
	}
	return (false);
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	ToxicSludgeBlock::update(Grid &grid, const int x, const int y)
{
	// Converts Water to ToxicSludge
	convertWater(grid, x, y);

	// Evaporates to FlammableGas
	if (evaporate(grid, x, y))
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
}
