#include "StoneBlock.hpp"

StoneBlock::StoneBlock()
{
	setId(STONE_BLOCK);

	randomizeColor();
}

ABlock	*StoneBlock::clone() const
{
	return (new StoneBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	StoneBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.845f, 0.845f, 0.845f}); break ;
		case (1): setColor({0.805f, 0.805f, 0.805f}); break ;
		case (2): setColor({0.766f, 0.766f, 0.766f}); break ;
		case (3): setColor({0.725f, 0.725f, 0.725f}); break ;
		default: setColor({0.678f, 0.678f, 0.678f}); break ;
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	StoneBlock::update(Grid &grid, const int x, const int y)
{
	(void)grid;
	(void)x;
	(void)y;
}
