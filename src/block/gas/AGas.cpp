#include "AGas.hpp"

bool	AGas::swapAbove(Grid &grid, const int x, const int y)
{
	if (grid.getBlock(x, y - 1)
		&& (grid.getBlock(x, y - 1)->getType() == LIQUID_TYPE || grid.getBlock(x, y - 1)->getType() == POWDER_TYPE || grid.getBlock(x, y - 1)->getId() == FIRE_BLOCK))
	{
		grid.swapBlock(x, y - 1, this, x, y);
		setUpdate(true);
		grid.getBlock(x, y - 1)->setUpdate(true);
		return (true);
	}
	return (false);
}

bool	AGas::blockedMovements(Grid &grid, const int x, const int y)
{
	if (grid.getBlock(x, y - 1) || y == 0)
	{
		if (std::rand() % 2)
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
	}
	return (false);
}

bool	AGas::risingMovements(Grid &grid, const int x, const int y)
{
	const unsigned int	chance = std::rand() % 10;

	if (chance < 8 && riseUp(grid, x, y))
		return (true);
	else if (chance == 8 && riseLeft(grid, x, y))
		return (true);
	else if (riseRight(grid, x, y))
		return (true);
	return (false);
}
