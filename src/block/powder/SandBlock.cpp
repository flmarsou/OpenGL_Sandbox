#include "SandBlock.hpp"

SandBlock::SandBlock()
{
	setId(SAND_BLOCK);
	setType(POWDER_TYPE);

	randomizeColor();
}

ABlock	*SandBlock::clone() const
{
	return (new SandBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	SandBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({1.0f, 0.905f, 0.631f}); break ;
		case (1): setColor({1.0f, 0.882f, 0.533f});	break ;
		case (2): setColor({1.0f, 0.859f, 0.439f});	break ;
		case (3): setColor({1.0f, 0.835f, 0.341f});	break ;
		default: setColor({1.0f, 0.81f, 0.295f}); break ;
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	SandBlock::update(Grid &grid, const int x, const int y)
{
	// Movements
	if (isOnGround(grid, y))
		return ;
	if (fallDown(grid, x, y))
		return ;
	if (diagonalMovements(grid, x, y))
		return ;
	if (liquidMovements(grid, x, y))
		return ;
}
