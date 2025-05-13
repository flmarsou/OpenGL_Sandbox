#include "AshBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

AshBlock::AshBlock()
{
	setId(ASHBLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
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

void	AshBlock::update(Grid &grid, const int x, const int y)
{
	// Security
	if (isOnGround(grid, y))
		return ;

	// Falling
	if (fallDown(grid, x, y))
		return ;

	const bool	leftFirst = std::rand() % 100 < 50;

	// Diagonal Falls
	if (leftFirst)
	{
		if (fallLeft(grid, x, y))
			return ;
		if (fallRight(grid, x, y))
			return ;
	}
	else
	{
		if (fallRight(grid, x, y))
			return ;
		if (fallLeft(grid, x, y))
			return ;
	}
}
