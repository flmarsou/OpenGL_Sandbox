#include "C4Block.hpp"
#include "FireBlock.hpp"

C4Block::C4Block()
	:	_detonate(false)
{
	setId(C4_BLOCK);
	setType(ELECTRICITY_TYPE);

	randomizeColor();
}

ABlock	*C4Block::clone() const
{
	return (new C4Block());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	C4Block::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.85f, 0.83f, 0.70f}); break ;
		case (1): setColor({0.80f, 0.78f, 0.60f}); break ;
		case (2): setColor({0.75f, 0.73f, 0.55f}); break ;
		case (3): setColor({0.70f, 0.68f, 0.50f}); break ;
		default: setColor({0.65f, 0.63f, 0.45f}); break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static bool	isBlockResistant(const Grid &grid, const int explosionX, const int explosionY)
{
	const ABlock	*target = grid.getBlock(explosionX, explosionY);

	if (target && (target->getId() == STONE_BLOCK || target->getId() == METAL_BLOCK))
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
		if (temp && (temp->getId() == STONE_BLOCK || temp->getId() == METAL_BLOCK))
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
//   Utils                                                                    //
// ========================================================================== //

void	C4Block::floodFill(const Grid &grid, const int x, const int y) const
{
	ABlock	*block = grid.getBlock(x, y);
	if (!block || block->getId() != C4_BLOCK)
		return ;

	C4Block	*c4 = dynamic_cast<C4Block *>(block);
	if (c4->_detonate)
		return ;

	c4->_detonate = true;

	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == C4_BLOCK)
		floodFill(grid, x, y - 1);
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == C4_BLOCK)
		floodFill(grid, x - 1, y);
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == C4_BLOCK)
		floodFill(grid, x + 1, y);
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == C4_BLOCK)
		floodFill(grid, x, y + 1);
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	C4Block::update(Grid &grid, const int x, const int y)
{
	if (checkElectricity(grid, x, y))
		floodFill(grid, x, y);

	// Explosion
	if (this->_detonate)
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
}
