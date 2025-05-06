#include "WaterBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

WaterBlock::WaterBlock()
{
	setId(WATERBLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	WaterBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.102f, 0.518f, 0.722f});	// Very Light Blue
			break ;
		case (1):
			setColor({0.102f, 0.549f, 0.722f});	// Light Blue
			break ;
		case (2):
			setColor({0.102f, 0.580f, 0.722f});	// Blue
			break ;
		case (3):
			setColor({0.102f, 0.611f, 0.722f});	// Dark Blue
			break ;
		default:
			setColor({0.102f, 0.643f, 0.722f});	// Very Dark Blue
			break ;
	}
}

void	WaterBlock::update(Grid &grid, const int x, const int y)
{
	const unsigned int	chance = std::rand() % 100;

	// Color
	if (chance == 1)
		randomizeColor();

	// Swap
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == SANDBLOCK)
	{
		grid.swapBlock(x, y - 1, this, x, y);
		setUpdate(true);
		grid.getBlock(x, y - 1)->setUpdate(true);
		return;
	}

	// Security & Movement
	if (y + 1 >= grid.getSize())
	{
		if (chance <= 50)
		{
			if (moveLeft(grid, x, y))
				return ;
			else if (moveRight(grid, x, y))
				return ;
		}
		else
		{
			if (moveRight(grid, x, y))
				return ;
			else if (moveLeft(grid, x, y))
				return ;
		}
		setUpdate(true);
		return ;
	}

	// Movement
	if (fallDown(grid, x, y))
		return ;
	else
	{
		if (chance <= 50)
		{
			if (fallLeft(grid, x, y))
				return ;
			else if (moveLeft(grid, x, y))
				return ;
			else if (fallRight(grid, x, y))
				return ;
			else if (moveRight(grid, x, y))
				return ;
		}
		else
		{
			if (fallRight(grid, x, y))
				return ;
			else if (moveRight(grid, x, y))
				return ;
			else if (fallLeft(grid, x, y))
				return ;
			else if (moveLeft(grid, x, y))
				return ;
		}
	}
}
