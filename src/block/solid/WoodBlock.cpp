#include "WoodBlock.hpp"
#include "FireBlock.hpp"
#include "AshBlock.hpp"

WoodBlock::WoodBlock()
	:	_burning(false)
{
	setId(WOOD_BLOCK);

	randomizeColor();
}

ABlock	*WoodBlock::clone() const
{
	return (new WoodBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	WoodBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.71f, 0.42f, 0.27f}); break ;
		case (1): setColor({0.60f, 0.36f, 0.22f}); break ;
		case (2): setColor({0.52f, 0.31f, 0.18f}); break ;
		case (3): setColor({0.43f, 0.26f, 0.14f}); break ;
		default: setColor({0.35f, 0.20f, 0.10f}); break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

void	WoodBlock::checkSurrounding(Grid &grid, const int x, const int y)
{
	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == FIRE_BLOCK)
		this->_burning = true;
	// Top Left
	if (grid.getBlock(x - 1, y - 1) && grid.getBlock(x - 1, y - 1)->getId() == FIRE_BLOCK)
		this->_burning = true;
	// Top Right
	if (grid.getBlock(x + 1, y - 1) && grid.getBlock(x + 1, y - 1)->getId() == FIRE_BLOCK)
		this->_burning = true;
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == FIRE_BLOCK)
		this->_burning = true;
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == FIRE_BLOCK)
		this->_burning = true;
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == FIRE_BLOCK)
		this->_burning = true;
	// Bottom Left
	if (grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getId() == FIRE_BLOCK)
		this->_burning = true;
	// Bottom Right
	if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getId() == FIRE_BLOCK)
		this->_burning = true;
}

static void	spreadFire(Grid &grid, const int x, const int y)
{
	const unsigned int	chance = std::rand() % 100;

	// Sideways
	if (chance < 15)
	{
		grid.setBlock(x, y - 1, new FireBlock());
		grid.setBlock(x, y + 1, new FireBlock());
		grid.setBlock(x - 1, y, new FireBlock());
		grid.setBlock(x + 1, y, new FireBlock());
	}
	// Diagonals
	if (chance < 10)
	{
		grid.setBlock(x - 1, y - 1, new FireBlock());
		grid.setBlock(x + 1, y - 1, new FireBlock());
		grid.setBlock(x - 1, y + 1, new FireBlock());
		grid.setBlock(x + 1, y + 1, new FireBlock());
	}
	// Burn
	if (chance == 50)
	{
		grid.deleteBlock(x, y);
		if (std::rand() % 2)
			grid.setBlock(x, y, new AshBlock());
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	WoodBlock::update(Grid &grid, const int x, const int y)
{
	if (!this->_burning)
	{
		checkSurrounding(grid, x, y);
		return ;
	}

	spreadFire(grid, x, y);
}
