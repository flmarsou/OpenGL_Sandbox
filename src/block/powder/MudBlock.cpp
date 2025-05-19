#include "MudBlock.hpp"

MudBlock::MudBlock()
	:	_stuck(false)
{
	setId(MUD_BLOCK);
	setType(POWDER_TYPE);

	randomizeColor();
}

ABlock	*MudBlock::clone() const
{
	return (new MudBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	MudBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.545f, 0.271f, 0.075f});	// Very Light Brown
			break ;
		case (1):
			setColor({0.502f, 0.235f, 0.063f});	// Light Brown
			break ;
		case (2):
			setColor({0.424f, 0.204f, 0.051f});	// Brown
			break ;
		case (3):
			setColor({0.361f, 0.165f, 0.035f});	// Dark Brown
			break ;
		default:
			setColor({0.314f, 0.133f, 0.027f});	// Very Dark Brown
			break ;
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	MudBlock::update(Grid &grid, const int x, const int y)
{
	// Movements
	if (isOnGround(grid, y))
		return ;
	if (fallDown(grid, x, y))
	{
		this->_stuck = false;
		return ;
	}

	// Stuck Movement
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getType() != LIQUID_TYPE && !this->_stuck)
	{
		if (std::rand() % 100 < 10)
			this->_stuck = true;
	}

	if (this->_stuck)
	{
		this->setUpdate(true);
		return ;
	}

	if (diagonalMovements(grid, x, y))
		return ;
	if (liquidMovements(grid, x, y))
		return ;
}
