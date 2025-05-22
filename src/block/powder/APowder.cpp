#include "APowder.hpp"

bool	APowder::liquidMovements(Grid &grid, const int x, const int y)
{
	const bool	leftFirst = std::rand() % 2;

	if (leftFirst && grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getType() == LIQUID_TYPE)
	{
		if (std::rand() % 100 != 1 && grid.getBlock(x - 1, y + 1)->getId() == LAVA_BLOCK)
			return (false);
		grid.swapBlock(x - 1, y + 1, this, x, y);
		setUpdate(true);
		grid.getBlock(x - 1, y + 1)->setUpdate(true);
		return (true);
	}
	else if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getType() == LIQUID_TYPE)
	{
		if (std::rand() % 100 != 1 && grid.getBlock(x + 1, y + 1)->getId() == LAVA_BLOCK)
			return (false);
		grid.swapBlock(x + 1, y + 1, this, x, y);
		setUpdate(true);
		grid.getBlock(x + 1, y + 1)->setUpdate(true);
		return (true);
	}
	return (false);
}

bool	APowder::diagonalMovements(Grid &grid, const int x, const int y)
{
	const bool	leftFirst = std::rand() % 2;

	if (leftFirst)
	{
		if (fallLeft(grid, x, y))
			return (true);
		if (fallRight(grid, x, y))
			return (true);
	}
	else
	{
		if (fallRight(grid, x, y))
			return (true);
		if (fallLeft(grid, x, y))
			return (true);
	}
	return (false);
}
