#include "FireBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

FireBlock::FireBlock()
{
	setId(FIREBLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	FireBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({1.0f, 1.0f, 0.8f});	// White
			break ;
		case (1):
			setColor({1.0f, 0.9f, 0.0f});	// Yellow
			break ;
		case (2):
			setColor({1.0f, 0.5f, 0.0f});	// Orange
			break ;
		case (3):
			setColor({0.9f, 0.1f, 0.0f});	// Red-Orange
			break ;
		default:
			setColor({0.6f, 0.0f, 0.0f});	// Red
			break ;
	}
}

void	FireBlock::update(Grid &grid, const int x, const int y)
{
	// TODO: Make fire versatile
	const unsigned int	chance = std::rand() % 100;

	if (chance < 25)
		grid.deleteBlock(x, y);
	(void)grid;
	(void)x;
	(void)y;
}
