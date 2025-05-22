#include "DynamiteBlock.hpp"
#include "FireBlock.hpp"

DynamiteBlock::DynamiteBlock()
{
	setId(DYNAMITE_BLOCK);
	setType(POWDER_TYPE);

	randomizeColor();
}

ABlock	*DynamiteBlock::clone() const
{
	return (new DynamiteBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	DynamiteBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.8f, 0.0f, 0.0f}); break ;
		case (1): setColor({0.9f, 0.1f, 0.1f}); break ;
		case (2): setColor({0.75f, 0.05f, 0.05f}); break ;
		case (3): setColor({0.85f, 0.15f, 0.15f}); break ;
		default: setColor({0.95f, 0.2f, 0.2f}); break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static bool	checkFire(const Grid &grid, const int x, const int y)
{
	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getHot())
		return (true);
	// Top Left
	if (grid.getBlock(x - 1, y - 1) && grid.getBlock(x - 1, y - 1)->getHot())
		return (true);
	// Top Right
	if (grid.getBlock(x + 1, y - 1) && grid.getBlock(x + 1, y - 1)->getHot())
		return (true);
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getHot())
		return (true);
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getHot())
		return (true);
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getHot())
		return (true);
	// Bottom Left
	if (grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getHot())
		return (true);
	// Bottom Right
	if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getHot())
		return (true);
	return (false);
}

static bool	isBlockResistant(const Grid &grid, const int explosionX, const int explosionY)
{
	const ABlock *target = grid.getBlock(explosionX, explosionY);

	if (target && target->getId() == STONE_BLOCK)
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
		if (temp && temp->getId() == STONE_BLOCK)
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

static bool	isExplosionShape(const int x, const int y, const int explosionX, const int explosionY, const int radius)
{
	int	dx = explosionX - x;
	int	dy = explosionY - y;
	return (dx * dx + dy * dy <= radius * radius);
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	DynamiteBlock::update(Grid &grid, const int x, const int y)
{
	// Explosion
	if (checkFire(grid, x, y))
	{
		grid.deleteBlock(x, y);

		const int	radius = 5;

		for (int offsetY = -radius; offsetY <= radius; offsetY++)
			for (int offsetX = -radius; offsetX <= radius; offsetX++)
			{
				int	explosionX = x + offsetX;
				int	explosionY = y + offsetY;

				// Checks if the explosion radius is correct.
				if (!isExplosionShape(x, y, explosionX, explosionY, radius))
					continue ;

				// Checks if nothing is blocking the path of the explosion.
				if (isExplosionBlocked(grid, x, y, explosionX, explosionY))
					continue ;

				// Checks if the block should be explosed.
				if (isBlockResistant(grid, explosionX, explosionY))
					continue ;

				grid.deleteBlock(explosionX, explosionY);
				grid.setBlock(explosionX, explosionY, new FireBlock(25));
			}
		return ;
	}

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
