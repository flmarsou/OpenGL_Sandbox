#include "FireBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

FireBlock::FireBlock()
	:	_extinguishRate(50), _extinguishColor(0)
{
	setId(FIREBLOCK);

	randomizeYellow();
}

FireBlock::FireBlock(unsigned int extinguishRate)
	:	_extinguishRate(extinguishRate), _extinguishColor(0)
{
	setId(FIREBLOCK);

	randomizeYellow();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	FireBlock::randomizeYellow()
{
	const unsigned int	chance = std::rand() % 3;

	switch (chance)
	{
		case (0):
			setColor({1.0f, 0.95f, 0.7f});		// Light
			break ;
		case (1):
			setColor({1.0f, 0.92f, 0.6f});		// Normal
			break ;
		default:
			setColor({1.0f, 0.98f, 0.5f});		// Dark
			break ;
	}
}

void	FireBlock::randomizeDarkYellow()
{
	const unsigned int	chance = std::rand() % 3;

	switch (chance)
	{
		case (0):
			setColor({0.9f, 0.75f, 0.3f});		// Light
			break ;
		case (1):
			setColor({0.85f, 0.7f, 0.2f});		// Normal
			break ;
		default:
			setColor({0.8f, 0.65f, 0.1f});		// Dark
			break ;
	}
}

void	FireBlock::randomizeOrange()
{
	const unsigned int	chance = std::rand() % 3;

	switch (chance)
	{
		case (0):
			setColor({1.0f, 0.6f, 0.2f});		// Light
			break ;
		case (1):
			setColor({1.0f, 0.55f, 0.1f});		// Normal
			break ;
		default:
			setColor({0.95f, 0.5f, 0.05f});		// Dark
			break ;
	}
}

void	FireBlock::randomizeDarkOrange()
{
	const unsigned int	chance = std::rand() % 3;

	switch (chance)
	{
		case (0):
			setColor({0.9f, 0.3f, 0.1f});		// Light
			break ;
		case (1):
			setColor({0.85f, 0.25f, 0.05f});	// Normal
			break ;
		default:
			setColor({0.8f, 0.2f, 0.05f});		// Dark
			break ;
	}
}

void	FireBlock::randomizeRed()
{
	const unsigned int	chance = std::rand() % 3;

	switch (chance)
	{
		case (0):
			setColor({0.8f, 0.1f, 0.05f});		// Light
			break ;
		case (1):
			setColor({0.75f, 0.05f, 0.05f});	// Normal
			break ;
		default:
			setColor({0.7f, 0.0f, 0.0f});		// Dark
			break ;
	}
}

bool	FireBlock::extinguishRate()
{
	switch (this->_extinguishColor)
	{
		case (0):
			randomizeDarkYellow();
			break;
		case (1):
			randomizeOrange();
			break;
		case (2):
			randomizeDarkOrange();
			break;
		case (3):
			randomizeRed();
			break;
		default:
			return (true);
	}
	this->_extinguishColor++;
	return (false);
}

void	FireBlock::update(Grid &grid, const int x, const int y)
{
	// Extinguish
	if (std::rand() % 100 < this->_extinguishRate)
	{
		if (extinguishRate())
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
