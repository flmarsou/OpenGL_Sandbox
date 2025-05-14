#include "AcidBlock.hpp"

AcidBlock::AcidBlock()
{
	setId(ACID_BLOCK);
	setType(LIQUID_TYPE);

	randomizeColor();
}

// ========================================================================== //
//   Colors                                                                   //
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

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

bool	AcidBlock::dissolveBehavior(Grid &grid, const int x, const int y)
{
	const unsigned int	id = grid.getBlock(x, y)->getId();

	// 100%
	if (id == SAND_BLOCK || id == ASH_BLOCK || id == WOOD_BLOCK || id == TOXIC_SLUDGE_BLOCK || id == MUD_BLOCK)
	{
		grid.deleteBlock(x, y);
		return (true);
	}

	// 5%
	if (std::rand() % 100 < 5 && id == STONE_BLOCK)
	{
		grid.deleteBlock(x, y);
		return (true);
	}

	// ToxicSludge Spawn
	if (id == WATER_BLOCK)
	{
		grid.deleteBlock(x, y);
		grid.setBlock(x, y, new ToxicSludgeBlock());
	}

	return (false);
}

bool	AcidBlock::dissolveSurrounding(Grid &grid, const int x, const int y)
{
	const unsigned int	skipChance = std::rand() % 100;
	const unsigned int	killChance = std::rand() % 100;
	bool				dissolved = false;

	// Attempts to dissolve with 25% chance
	if (skipChance < 75)
		return (true);

	if (grid.getBlock(x, y + 1)			// Bottom
		|| grid.getBlock(x - 1, y)		// Left
		|| grid.getBlock(x + 1, y)		// Right
		|| grid.getBlock(x, y - 1))		// Top
	{
		if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() != ACID_BLOCK)
			dissolved = dissolveBehavior(grid, x, y + 1);
		if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() != ACID_BLOCK)
			dissolved = dissolveBehavior(grid, x - 1, y);
		if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() != ACID_BLOCK)
			dissolved = dissolveBehavior(grid, x + 1, y);
		if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() != ACID_BLOCK)
			dissolved = dissolveBehavior(grid, x, y - 1);
	}

	// Kills the acid block if it dissolved something with 50% chance
	if (dissolved && killChance < 50)
		return (false);

	return (true);
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

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

	// Security & Movements
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
