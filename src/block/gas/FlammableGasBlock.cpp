#include "FlammableGasBlock.hpp"
#include "FireBlock.hpp"

FlammableGasBlock::FlammableGasBlock()
	:	_burning(false)
{
	setId(FLAMMABLE_GAS_BLOCK);

	randomizeColor();
}

ABlock	*FlammableGasBlock::clone() const
{
	return (new FlammableGasBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	FlammableGasBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.75f, 0.90f, 0.75f}); break ;
		case (1): setColor({0.70f, 0.85f, 0.70f}); break ;
		case (2): setColor({0.65f, 0.80f, 0.65f}); break ;
		case (3): setColor({0.60f, 0.75f, 0.60f}); break ;
		default: setColor({0.55f, 0.70f, 0.55f}); break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

bool	FlammableGasBlock::checkFire(Grid &grid, const int x, const int y) const
{
	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == FIRE_BLOCK)
		return (true);
	// Top Left
	if (grid.getBlock(x - 1, y - 1) && grid.getBlock(x - 1, y - 1)->getId() == FIRE_BLOCK)
		return (true);
	// Top Right
	if (grid.getBlock(x + 1, y - 1) && grid.getBlock(x + 1, y - 1)->getId() == FIRE_BLOCK)
		return (true);
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == FIRE_BLOCK)
		return (true);
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == FIRE_BLOCK)
		return (true);
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == FIRE_BLOCK)
		return (true);
	// Bottom Left
	if (grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getId() == FIRE_BLOCK)
		return (true);
	// Bottom Right
	if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getId() == FIRE_BLOCK)
		return (true);

	return (false);
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	FlammableGasBlock::update(Grid &grid, const int x, const int y)
{
	// Burning
	this->_burning = checkFire(grid, x, y);

	if (this->_burning && std::rand() % 100 < 10)
	{
		grid.convertBlock(x, y, new FireBlock(10));
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
