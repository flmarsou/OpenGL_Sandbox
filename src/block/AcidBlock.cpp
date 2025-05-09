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
			setColor({0.102f, 0.722f, 0.290f});	// Very Light Green
			break ;
		case (1):
			setColor({0.102f, 0.690f, 0.290f});	// Light Green
			break ;
		case (2):
			setColor({0.102f, 0.659f, 0.290f});	// Green
			break ;
		case (3):
			setColor({0.102f, 0.627f, 0.290f});	// Dark Green
			break ;
		default:
			setColor({0.102f, 0.596f, 0.290f});	// Very Dark Green
			break ;
	}
}

bool	AcidBlock::dissolveSurrounding(Grid &grid, const int x, const int y)
{
	const unsigned int	skipChance = std::rand() % 100;
	const unsigned int	killChance = std::rand() % 100;
	bool				dissolved = false;

	// Attempts to dissolve with 75% chance
	if (skipChance < 75)
		return (true);

	if (grid.getBlock(x, y + 1)			// Bottom
		|| grid.getBlock(x - 1, y)		// Left
		|| grid.getBlock(x + 1, y)		// Right
		|| grid.getBlock(x, y - 1))		// Top
	{
		if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() != ACIDBLOCK)
		{
			grid.deleteBlock(x, y + 1);
			dissolved = true;
		}
		if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() != ACIDBLOCK)
		{
			grid.deleteBlock(x - 1, y);
			dissolved = true;
		}
		if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() != ACIDBLOCK)
		{
			grid.deleteBlock(x + 1, y);
			dissolved = true;
		}
		if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() != ACIDBLOCK)
		{
			grid.deleteBlock(x, y - 1);
			dissolved = true;
		}
	}

	// Kills the acid block if it dissolved something with 50% chance
	if (dissolved && killChance < 50)
		return (false);

	return (true);
}

void	AcidBlock::update(Grid &grid, const int x, const int y)
{
	// Color
	if (std::rand() % 200 == 1)
		randomizeColor();

	// Dissolve
	if (!dissolveSurrounding(grid, x, y))
	{
		grid.deleteBlock(x, y);
		return ;
	}

	const bool	leftFirst = std::rand() % 100 <= 50;

	// Security & Movement
	if (isOnGround(grid, y))
	{
		if (leftFirst)
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
		return ;
	}

	// Falling
	if (fallDown(grid, x, y))
		return ;

	// Diagonal Falls & Movements
	if (leftFirst)
	{
		if (fallLeft(grid, x, y))
			return ;
		if (moveLeft(grid, x, y))
			return ;
		if (fallRight(grid, x, y))
			return ;
		if (moveRight(grid, x, y))
			return ;
	}
	else
	{
		if (fallRight(grid, x, y))
			return ;
		if (moveRight(grid, x, y))
			return ;
		if (fallLeft(grid, x, y))
			return ;
		if (moveLeft(grid, x, y))
			return ;
	}
}
