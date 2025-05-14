#include "SandBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

SandBlock::SandBlock()
{
	setId(SAND_BLOCK);
	setType(POWDER_TYPE);

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
			setColor({1.0f, 0.81f, 0.295f});	// Very Dark Yellow
			break ;
	}
}

void	SandBlock::update(Grid &grid, const int x, const int y)
{
	// Security
	if (isOnGround(grid, y))
		return ;

	// Falling
	if (fallDown(grid, x, y))
		return ;

	// Diagonal Falls
	const bool	leftFirst = std::rand() % 2;

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

	// Diagonal Falls in water
	if (leftFirst && grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getId() == WATER_BLOCK)
	{
		grid.swapBlock(x - 1, y + 1, this, x, y);
		setUpdate(true);
		grid.getBlock(x - 1, y + 1)->setUpdate(true);
		return ;
	}
	else if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getId() == WATER_BLOCK)
	{
		grid.swapBlock(x + 1, y + 1, this, x, y);
		setUpdate(true);
		grid.getBlock(x + 1, y + 1)->setUpdate(true);
		return ;
	}
}
