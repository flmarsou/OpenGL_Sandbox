#include "StoneBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

StoneBlock::StoneBlock()
{
	setId(STONEBLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	StoneBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.845f, 0.845f, 0.845f});	// Very Light Gray
			break ;
		case (1):
			setColor({0.805f, 0.805f, 0.805f});	// Light Gray
			break ;
		case (2):
			setColor({0.766f, 0.766f, 0.766f});	// Gray
			break ;
		case (3):
			setColor({0.725f, 0.725f, 0.725f});	// Dark Gray
			break ;
		default:
			setColor({0.678f, 0.678f, 0.678f});	// Very Dark Gray
			break ;
	}
}

void	StoneBlock::update(Grid &grid, const int x, const int y)
{
	(void)grid;
	(void)x;
	(void)y;
}
