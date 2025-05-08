#include "FireBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

FireBlock::FireBlock(unsigned int extinguishRate)
	:	_extinguishRate(extinguishRate)
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
			setColor({1.0f, 0.95f, 0.8f});	// Yellow
			break ;
		case (1):
			setColor({1.0f, 0.85f, 0.4f});	// Orange
			break ;
		case (2):
			setColor({1.0f, 0.6f, 0.2f});	// Orange
			break ;
		case (3):
			setColor({0.9f, 0.3f, 0.1f});	// Red-Orange
			break ;
		default:
			setColor({0.8f, 0.1f, 0.05f});	// Red
			break ;
	}
}

void	FireBlock::update(Grid &grid, const int x, const int y)
{
	// Extinguish
	if (std::rand() % 100 < this->_extinguishRate)
	{
		grid.deleteBlock(x, y);
		return ;
	}

	// Security & Movement
	if (y == 0)
	{
		if (std::rand() % 2)
		{
			if (moveLeft(grid, x, y))
				return ;
			if (moveRight(grid, x, y))
				return ;
		}
		else
		{
			if (moveRight(grid, x, y))
				return ;
			if (moveLeft(grid, x, y))
				return ;
		}
	}

	// Rising Movements
	unsigned int	direction[3] = {0, 1, 2};	// Up (0), Left (1), Right (2)

	// Fisher-Yates Shuffle Algorithm
	for (int i = 2; i >= 0; i--)
	{
		unsigned int	chance = std::rand() % (i + 1);
		unsigned int	temp = direction[i];

		direction[i] = direction[chance];
		direction[chance] = temp;
	}

	for (unsigned int i = 0; i < 3; i++)
	{
		switch (direction[i])
		{
			case (0):
				if (riseUp(grid, x, y))
					return ;
				break ;

			case (1):
				if (riseLeft(grid, x, y))
					return ;
				break ;

			default:
				if (riseRight(grid, x, y))
					return ;
				break ;
		}
	}
}
