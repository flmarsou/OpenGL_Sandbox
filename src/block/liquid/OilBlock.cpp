#include "OilBlock.hpp"
#include "FireBlock.hpp"

OilBlock::OilBlock()
	:	_burning(false)
{
	setId(OIL_BLOCK);
	setType(LIQUID_TYPE);

	randomizeColor();
}

ABlock *OilBlock::clone() const
{
	return (new OilBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	OilBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.749f, 0.682f, 0.231f}); break;
		case (1): setColor({0.788f, 0.682f, 0.180f}); break;
		case (2): setColor({0.725f, 0.639f, 0.251f}); break;
		case (3): setColor({0.792f, 0.725f, 0.247f}); break;
		default: setColor({0.714f, 0.659f, 0.200f}); break;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

void	OilBlock::checkFire(Grid &grid, const int x, const int y)
{
	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == FIRE_BLOCK)
	{
		this->_burning = true;
		return ;
	}
	// Top Left
	if (grid.getBlock(x - 1, y - 1) && grid.getBlock(x - 1, y - 1)->getId() == FIRE_BLOCK)
	{
		this->_burning = true;
		return ;
	}
	// Top Right
	if (grid.getBlock(x + 1, y - 1) && grid.getBlock(x + 1, y - 1)->getId() == FIRE_BLOCK)
	{
		this->_burning = true;
		return ;
	}
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == FIRE_BLOCK)
	{
		this->_burning = true;
		return ;
	}
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == FIRE_BLOCK)
	{
		this->_burning = true;
		return ;
	}
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == FIRE_BLOCK)
	{
		this->_burning = true;
		return ;
	}
	// Bottom Left
	if (grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getId() == FIRE_BLOCK)
	{
		this->_burning = true;
		return ;
	}
	// Bottom Right
	if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getId() == FIRE_BLOCK)
	{
		this->_burning = true;
		return ;
	}
}

bool	OilBlock::spreadFire(Grid &grid, const int x, const int y)
{
	const unsigned int	chance = std::rand() % 100;

	// Top & Sides
	if (chance < 15)
	{
		grid.setBlock(x, y - 1, new FireBlock());
		grid.setBlock(x - 1, y - 1, new FireBlock());
		grid.setBlock(x + 1, y - 1, new FireBlock());
		grid.setBlock(x - 1, y, new FireBlock());
		grid.setBlock(x + 1, y, new FireBlock());
	}
	// Burn
	if (chance == 50)
	{
		grid.deleteBlock(x, y);
		return (true);
	}

	return (false);
}

bool	OilBlock::swapLiquids(Grid &grid, const int x, const int y)
{
	const unsigned int	chance = std::rand() % 3;

	switch (chance)
	{
		// Fall Down
		case (0):
		{
			if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getType() == LIQUID_TYPE && grid.getBlock(x, y - 1)->getId() != OIL_BLOCK)
			{
				grid.swapBlock(x, y - 1, this, x, y);
				setUpdate(true);
				grid.getBlock(x, y - 1)->setUpdate(true);
				return (true);
			}
			break ;
		}
		// Fall Left
		case (1):
		{
			if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getType() == LIQUID_TYPE && grid.getBlock(x - 1, y)->getId() != OIL_BLOCK)
			{
				grid.swapBlock(x - 1, y, this, x, y);
				setUpdate(true);
				grid.getBlock(x - 1, y)->setUpdate(true);
				return (true);
			}
			break ;
		}
		// Fall Right
		case (2):
		{
			if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getType() == LIQUID_TYPE && grid.getBlock(x + 1, y)->getId() != OIL_BLOCK)
			{
				grid.swapBlock(x + 1, y, this, x, y);
				setUpdate(true);
				grid.getBlock(x + 1, y)->setUpdate(true);
				return (true);
			}
			break ;
		}
	}

	return (false);
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	OilBlock::update(Grid &grid, const int x, const int y)
{
	// Burning
	if (!this->_burning)
		checkFire(grid, x, y);
	else if (spreadFire(grid, x, y))
		return ;

	// Color
	if (std::rand() % 100 == 1)
		randomizeColor();

	// Movements
	if (swapLiquids(grid, x, y))
		return ;
	if (swapAbove(grid, x, y))
		return ;
	if (groundMovements(grid, x, y))
		return ;
	if (fallDown(grid, x, y))
		return ;
	if (diagonalMovements(grid, x, y))
		return ;
}
