#include "AshBlock.hpp"

AshBlock::AshBlock()
{
	setId(ASH_BLOCK);
	setType(POWDER_TYPE);

	randomizeColor();
}

ABlock	*AshBlock::clone() const
{
	return (new AshBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	AshBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.5f, 0.5f, 0.5f});		// Very Light Gray
			break ;
		case (1):
			setColor({0.4f, 0.4f, 0.4f});		// Light Gray
			break ;
		case (2):
			setColor({0.3f, 0.3f, 0.3f});		// Gray
			break ;
		case (3):
			setColor({0.35f, 0.33f, 0.32f});	// Dark Gray
			break ;
		default:
			setColor({0.25f, 0.25f, 0.27f});	// Very Dark Gray
			break ;
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	AshBlock::update(Grid &grid, const int x, const int y)
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
