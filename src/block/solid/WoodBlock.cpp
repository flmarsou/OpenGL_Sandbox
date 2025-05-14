#include "WoodBlock.hpp"

WoodBlock::WoodBlock()
	:	_burning(false)
{
	setId(WOOD_BLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	WoodBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.71f, 0.42f, 0.27f});	// Light Brown (sanded oak)
			break ;
		case (1):
			setColor({0.60f, 0.36f, 0.22f});	// Brown (pine/mid-tone wood)
			break ;
		case (2):
			setColor({0.52f, 0.31f, 0.18f});	// Medium Brown
			break ;
		case (3):
			setColor({0.43f, 0.26f, 0.14f});	// Dark Brown (aged wood)
			break ;
		default:
			setColor({0.35f, 0.20f, 0.10f});	// Very Dark Brown (rich walnut)
			break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

void	WoodBlock::checkSurrounding(Grid &grid, const int x, const int y)
{
	if (grid.getBlock(x, y + 1)			// Bottom
		|| grid.getBlock(x - 1, y + 1)	// Bottom Left
		|| grid.getBlock(x + 1, y + 1)	// Bottom Right
		|| grid.getBlock(x - 1, y)		// Left
		|| grid.getBlock(x + 1, y)		// Right
		|| grid.getBlock(x, y - 1)		// Top
		|| grid.getBlock(x - 1, y - 1)	// Top Left
		|| grid.getBlock(x + 1, y - 1))	// Top Right
	{
		if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == FIRE_BLOCK)
			this->_burning = true;
		if (grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getId() == FIRE_BLOCK)
			this->_burning = true;
		if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getId() == FIRE_BLOCK)
			this->_burning = true;
		if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == FIRE_BLOCK)
			this->_burning = true;
		if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == FIRE_BLOCK)
			this->_burning = true;
		if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == FIRE_BLOCK)
			this->_burning = true;
		if (grid.getBlock(x - 1, y - 1) && grid.getBlock(x - 1, y - 1)->getId() == FIRE_BLOCK)
			this->_burning = true;
		if (grid.getBlock(x + 1, y - 1) && grid.getBlock(x + 1, y - 1)->getId() == FIRE_BLOCK)
			this->_burning = true;
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	WoodBlock::update(Grid &grid, const int x, const int y)
{
	checkSurrounding(grid, x, y);

	if (!this->_burning)
		return ;

	const unsigned int	chance = std::rand() % 100;

	// Spread fire
	if (chance < 15)
	{
		grid.setBlock(x, y - 1, new FireBlock());
		grid.setBlock(x, y + 1, new FireBlock());
		grid.setBlock(x - 1, y, new FireBlock());
		grid.setBlock(x + 1, y, new FireBlock());
	}
	if (chance < 10)
	{
		grid.setBlock(x - 1, y - 1, new FireBlock());
		grid.setBlock(x + 1, y - 1, new FireBlock());
		grid.setBlock(x - 1, y + 1, new FireBlock());
		grid.setBlock(x + 1, y + 1, new FireBlock());
	}

	// Burn
	if (chance == 15)
	{
		grid.deleteBlock(x, y);
		if (std::rand() % 2)
			grid.setBlock(x, y, new AshBlock());
	}

	// Extinguish
	if (chance < 20)
		this->_burning = false;
}
