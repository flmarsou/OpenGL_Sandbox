#include "FlammableGasBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

FlammableGasBlock::FlammableGasBlock()
{
	setId(FLAMMABLEGASBLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	FlammableGasBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.75f, 0.90f, 0.75f});	// Very Light Greenish Gray
			break ;
		case (1):
			setColor({0.70f, 0.85f, 0.70f});	// Light Greenish Gray
			break ;
		case (2):
			setColor({0.65f, 0.80f, 0.65f});	// Greenish Gray
			break ;
		case (3):
			setColor({0.60f, 0.75f, 0.60f});	// Dark Greenish Gray
			break ;
		default:
			setColor({0.55f, 0.70f, 0.55f});	// Very Dark Greenish Gray
			break ;
	}
}

void	FlammableGasBlock::update(Grid &grid, const int x, const int y)
{
	// Color
	if (std::rand() % 100 == 1)
		randomizeColor();

	// Security & Movement
	if (grid.getBlock(x, y - 1) || y == 0)
	{
		if (std::rand() % 2)
		{
			if (moveLeft(grid, x, y))
				return ;
			if (moveRight(grid, x, y))
				return ;
		}
		else
		{
			if (moveRight(grid, x, y))
				return ;
			if (moveLeft(grid, x, y))
				return ;
		}
	}

	// Rising Movements
	const unsigned int	chance = std::rand() % 10;

	if (chance < 8 && riseUp(grid, x, y))
		return ;
	else if (chance == 8 && riseLeft(grid, x, y))
		return ;
	else if (riseRight(grid, x, y))
		return ;
}
