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
		case (0):
			setColor({0.525f, 0.525f, 0.102f});	// Very Light Sluggish Green
			break ;
		case (1):
			setColor({0.604f, 0.651f, 0.118f});	// Light Sluggish Green
			break ;
		case (2):
			setColor({0.451f, 0.576f, 0.094f});	// Sluggish Green
			break ;
		case (3):
			setColor({0.400f, 0.502f, 0.078f});	// Dark Sluggish Green
			break ;
		default:
			setColor({0.380f, 0.455f, 0.078f});	// Very Dark Sluggish Green
			break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

void	ToxicSludgeBlock::convertSurrounding(Grid &grid, const int x, const int y)
{
	// Attempts to convert with 10% chance
	if (std::rand() % 100 < 90)
		return ;

	if (grid.getBlock(x, y + 1)			// Bottom
		|| grid.getBlock(x - 1, y)		// Left
		|| grid.getBlock(x + 1, y)		// Right
		|| grid.getBlock(x, y - 1))		// Top
	{
		if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == WATER_BLOCK)
			grid.convertBlock(x, y + 1, new ToxicSludgeBlock());
		if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == WATER_BLOCK)
			grid.convertBlock(x - 1, y, new ToxicSludgeBlock());
		if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == WATER_BLOCK)
			grid.convertBlock(x + 1, y, new ToxicSludgeBlock());
		if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == WATER_BLOCK)
			grid.convertBlock(x, y - 1, new ToxicSludgeBlock());
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	ToxicSludgeBlock::update(Grid &grid, const int x, const int y)
{
	// Converts Water to ToxicSludge
	convertSurrounding(grid, x, y);

	// Evaporate to FlammableGas
	if (!grid.getBlock(x, y - 1) && std::rand() % 1000 < 5)
	{
		grid.setBlock(x, y - 1, new FlammableGasBlock());
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
