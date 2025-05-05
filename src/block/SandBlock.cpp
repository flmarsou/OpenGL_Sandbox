#include "SandBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

SandBlock::SandBlock()
{
	setId(SANDBLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	SandBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({1.0f, 0.905f, 0.631f});	// Very Light Yellow
			break ;
		case (1):
			setColor({1.0f, 0.882f, 0.533f});	// Light Yellow
			break ;
		case (2):
			setColor({1.0f, 0.859f, 0.439f});	// Yellow
			break ;
		case (3):
			setColor({1.0f, 0.835f, 0.341f});	// Dark Yellow
			break ;
		default:
			setColor({1.0f, 0.784f, 0.251f});	// Very Dark Yellow
			break ;
	}
}

void	SandBlock::update(Grid &grid, const int x, const int y)
{
	// Security
	if (isOnGround(grid, y))
		return ;

	// Movements
	if (fallDown(grid, x, y))
		return ;
	else
	{
		const unsigned int	chance = std::rand() % 100;

		if (chance < 50)
		{
			if (fallLeft(grid, x, y))
				return ;
			else if (fallRight(grid, x, y))
				return ;
		}
		else
		{
			if (fallRight(grid, x, y))
				return ;
			else if (fallLeft(grid, x, y))
				return ;
		}
	}
}
