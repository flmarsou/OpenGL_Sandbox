#include "BombBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

BombBlock::BombBlock()
{
	setId(BOMBBLOCK);

	// TODO: Make better color
	setColor({1.0f, 0.0f, 0.0f});
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

static bool	isBlockResistant(const Grid &grid, const int explosionX, const int explosionY)
{
	const ABlock *target = grid.getBlock(explosionX, explosionY);

	if (target && target->getId() == STONEBLOCK)
		return (true);
	return (false);
}

static bool isExplosionBlocked(const Grid &grid, int x, int y, const int explosionX, const int explosionY)
{
	int	dx = std::abs(explosionX - x);	// Horizontal Distance
	int	dy = -std::abs(explosionY - y);	// Vertical Distance (negative to simplify the algorithm)
	int	sx = x < explosionX ? 1 : -1;	// Horizontal Step Direction (Right (+1), Left (-1))
	int	sy = y < explosionY ? 1 : -1;	// Vertical Step Direction (Down (+1), Up (-1))
	int	err = dx + dy;

	while (1)
	{
		// Origin
		if (x == explosionX && y == explosionY)
			break ;

		// Explosion Blocker
		const ABlock	*temp = grid.getBlock(x, y);
		if (temp && temp->getId() == STONEBLOCK)
			return (true);

		// Bresenham's Algorithm
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y += sy;
		}
	}
	return (false);
}

static bool	isExplosionShape(const int x, const int y, const int explosionX, const int explosionY)
{
	if (!(explosionY == y - 7 && (explosionX < x - 2 || explosionX > x + 2))
		&& !(explosionY == y - 6 && (explosionX < x - 4 || explosionX > x + 4))
		&& !(explosionY == y - 5 && (explosionX < x - 5 || explosionX > x + 5))
		&& !((explosionY == y - 4 || explosionY == y - 3) && (explosionX < x - 6 || explosionX > x + 6))
		&& !((explosionY == y + 3 || explosionY == y + 4) && (explosionX < x - 6 || explosionX > x + 6))
		&& !(explosionY == y + 5 && (explosionX < x - 5 || explosionX > x + 5))
		&& !(explosionY == y + 6 && (explosionX < x - 4 || explosionX > x + 4))
		&& !(explosionY == y + 7 && (explosionX < x - 2 || explosionX > x + 2)))
		return (true);
	return (false);
}

void	BombBlock::update(Grid &grid, const int x, const int y)
{
	// Security & Explosion
	if (isOnGround(grid, y) || (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() != BOMBBLOCK))
	{
		grid.deleteBlock(x, y);

		for (int explosionY = y - 7; explosionY < y + 8; explosionY++)
			for (int explosionX = x - 7; explosionX < x + 8; explosionX++)
			{
				// Checks if the explosion radius is correct.
				if (!isExplosionShape(x, y, explosionX, explosionY))
					continue ;

				// Checks if nothing is blocking the path of the explosion.
				if (isExplosionBlocked(grid, x, y, explosionX, explosionY))
					continue ;

				// Checks if the block should be explosed.
				if (isBlockResistant(grid, explosionX, explosionY))
					continue ;

				grid.deleteBlock(explosionX, explosionY);
				grid.setBlock(explosionX, explosionY, new FireBlock(10));
			}
		return ;
	}

	// Falling
	if (fallDown(grid, x, y))
		return ;
}
