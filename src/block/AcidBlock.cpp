#include "AcidBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

AcidBlock::AcidBlock()
{
	setId(ACIDBLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	AcidBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.102f, 0.518f, 0.722f});	// Very Light Blue
			break ;
		case (1):
			setColor({0.102f, 0.549f, 0.722f});	// Light Blue
			break ;
		case (2):
			setColor({0.102f, 0.580f, 0.722f});	// Blue
			break ;
		case (3):
			setColor({0.102f, 0.611f, 0.722f});	// Dark Blue
			break ;
		default:
			setColor({0.102f, 0.643f, 0.722f});	// Very Dark Blue
			break ;
	}
}

void	AcidBlock::setSeverity(const Grid &grid, const int &x, const int &y)
{
	if (grid.getBlock(x, y + 1)->getId() == SANDBLOCK)
		this->??? = STRONG;
	else if (grid.getBlock(x, y + 1)->getId() == STONEBLOCK
		|| grid.getBlock(x, y + 1)->getId() == WATERBLOCK)
		this->??? = WEAK;
}

bool	AcidBlock::checkSurrounding(const Grid &grid, const int &x, const int &y)
{
	bool	ret = false;

	if (grid.getBlock(x, y + 1)			// Down
		|| grid.getBlock(x - 1, y + 1)	// Down Left
		|| grid.getBlock(x + 1, y + 1)	// Down Right
		|| grid.getBlock(x - 1, y)		// Left
		|| grid.getBlock(x + 1, y)		// Right
		|| grid.getBlock(x, y - 1)		// Up
		|| grid.getBlock(x - 1, y - 1)	// Up Left
		|| grid.getBlock(x + 1, y - 1))	// Up Right
	{
		if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() != ACIDBLOCK)			// Bottom
		{
			ret = true;
		}
		if (grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getId() != ACIDBLOCK)	// Bottom Left
		{
			ret = true;
		}
		if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getId() != ACIDBLOCK)	// Bottom Right
		{
			ret = true;
		}
		if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() != ACIDBLOCK)			// Left
		{
			ret = true;
		}
		if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() != ACIDBLOCK)			// Right
		{
			ret = true;
		}
		if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() != ACIDBLOCK)			// Top
		{
			ret = true;
		}
		if (grid.getBlock(x - 1, y - 1) && grid.getBlock(x - 1, y - 1)->getId() != ACIDBLOCK)	// Top Left
		{
			ret = true;
		}
		if (grid.getBlock(x + 1, y - 1) && grid.getBlock(x + 1, y - 1)->getId() != ACIDBLOCK)	// Top Right
		{
			ret = true;
		}
	}
	return (ret);
}

void	AcidBlock::update(Grid &grid, const int x, const int y)
{
	const unsigned int	chance = std::rand() % 100;

	if (chance == 1)
		randomizeColor();

	// 
	if (checkSurrounding(grid, x, y))
	{
		
	}

	// Security & Movement
	if (y + 1 >= grid.getSize())
	{
		if (chance < 50)
		{
			if (moveLeft(grid, x, y))
				return ;
			else if (moveRight(grid, x, y))
				return ;
		}
		else
		{
			if (moveRight(grid, x, y))
				return ;
			else if (moveLeft(grid, x, y))
				return ;
		}
		setUpdate(true);
		return ;
	}

	// Movement
	if (fallDown(grid, x, y))
		return ;
	else
	{
		if (chance < 50)
		{
			if (fallLeft(grid, x, y))
				return ;
			else if (moveLeft(grid, x, y))
				return ;
			else if (fallRight(grid, x, y))
				return ;
			else if (moveRight(grid, x, y))
				return ;
		}
		else
		{
			if (fallRight(grid, x, y))
				return ;
			else if (moveRight(grid, x, y))
				return ;
			else if (fallLeft(grid, x, y))
				return ;
			else if (moveLeft(grid, x, y))
				return ;
		}
	}
}
