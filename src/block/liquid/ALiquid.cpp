#include "ALiquid.hpp"

bool	ALiquid::swapAbove(Grid &grid, const int x, const int y)
{
	if (grid.getBlock(x, y - 1)
		&& grid.getBlock(x, y - 1)->getType() == POWDER_TYPE)
	{
		grid.swapBlock(x, y - 1, this, x, y);
		setUpdate(true);
		grid.getBlock(x, y - 1)->setUpdate(true);
		return (true);
	}
	return (false);
}

bool	ALiquid::groundMovements(Grid &grid, const int x, const int y)
{
	const bool	leftFirst = std::rand() % 2;

	if (isOnGround(grid, y))
	{
		if (leftFirst)
		{
			if (moveLeft(grid, x, y))
				return (true);
			if (moveRight(grid, x, y))
				return (true);
		}
		else
		{
			if (moveRight(grid, x, y))
				return (true);
			if (moveLeft(grid, x, y))
				return (true);
		}
		return (true);
	}
	return (false);
}

bool	ALiquid::diagonalMovements(Grid &grid, const int x, const int y)
{
	const bool	leftFirst = std::rand() % 2;

	if (leftFirst)
	{
		if (fallLeft(grid, x, y))
			return (true);
		if (moveLeft(grid, x, y))
			return (true);
		if (fallRight(grid, x, y))
			return (true);
		if (moveRight(grid, x, y))
			return (true);
	}
	else
	{
		if (fallRight(grid, x, y))
			return (true);
		if (moveRight(grid, x, y))
			return (true);
		if (fallLeft(grid, x, y))
			return (true);
		if (moveLeft(grid, x, y))
			return (true);
	}
	return (false);
}
