#include "WoodBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

WoodBlock::WoodBlock()
	:	_burned(false)
{
	setId(WOODBLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
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

void	WoodBlock::update(Grid &grid, const int x, const int y)
{
	const unsigned int	chance = std::rand() % 100;

	if (grid.getBlock(x, y + 1)			// Bottom
		|| grid.getBlock(x - 1, y + 1)	// Bottom Left
		|| grid.getBlock(x + 1, y + 1)	// Bottom Right
		|| grid.getBlock(x - 1, y)		// Left
		|| grid.getBlock(x + 1, y)		// Right
		|| grid.getBlock(x, y - 1)		// Top
		|| grid.getBlock(x - 1, y - 1)	// Top Left
		|| grid.getBlock(x + 1, y - 1))	// Top Right
	{
		if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == FIREBLOCK)
			this->_burned = true;
		if (grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getId() == FIREBLOCK)
			this->_burned = true;
		if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getId() == FIREBLOCK)
			this->_burned = true;
		if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == FIREBLOCK)
			this->_burned = true;
		if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == FIREBLOCK)
			this->_burned = true;
		if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == FIREBLOCK)
			this->_burned = true;
		if (grid.getBlock(x - 1, y - 1) && grid.getBlock(x - 1, y - 1)->getId() == FIREBLOCK)
			this->_burned = true;
		if (grid.getBlock(x + 1, y - 1) && grid.getBlock(x + 1, y - 1)->getId() == FIREBLOCK)
			this->_burned = true;
	}

	// TODO: Burn behavior
}
