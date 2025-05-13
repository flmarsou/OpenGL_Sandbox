#include "ToxicSludgeBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

ToxicSludgeBlock::ToxicSludgeBlock()
{
	setId(TOXIC_SLUDGE_BLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	ToxicSludgeBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.525f, 0.525f, 0.102f});	// Very Light Sluggish Green
			break ;
		case (1):
			setColor({0.604f, 0.651f, 0.118f});	// Light Sluggish Green
			break ;
		case (2):
			setColor({0.451f, 0.576f, 0.094f});	// Sluggish Green
			break ;
		case (3):
			setColor({0.400f, 0.502f, 0.078f});	// Dark Sluggish Green
			break ;
		default:
			setColor({0.380f, 0.455f, 0.078f});	// Very Dark Sluggish Green
			break ;
	}
}

void	ToxicSludgeBlock::convertSurrounding(Grid &grid, const int x, const int y)
{
	// Attempts to convert with 10% chance
	if (std::rand() % 100 < 90)
		return ;

	if (grid.getBlock(x, y + 1)			// Bottom
		|| grid.getBlock(x - 1, y)		// Left
		|| grid.getBlock(x + 1, y)		// Right
		|| grid.getBlock(x, y - 1))		// Top
	{
		if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == WATER_BLOCK)
			grid.convertBlock(x, y + 1, new ToxicSludgeBlock());
		if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == WATER_BLOCK)
			grid.convertBlock(x - 1, y, new ToxicSludgeBlock());
		if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == WATER_BLOCK)
			grid.convertBlock(x + 1, y, new ToxicSludgeBlock());
		if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == WATER_BLOCK)
			grid.convertBlock(x, y - 1, new ToxicSludgeBlock());
	}
}

void	ToxicSludgeBlock::update(Grid &grid, const int x, const int y)
{
	convertSurrounding(grid, x, y);

	// Evaporate and FlammableGas Spawn
	if (!grid.getBlock(x, y - 1) && std::rand() % 1000 < 5)
	{
		grid.setBlock(x, y - 1, new FlammableGasBlock());
		grid.deleteBlock(x, y);
		return ;
	}

	// Color
	if (std::rand() % 100 == 1)
		randomizeColor();

	// Swap Above
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == SAND_BLOCK)
	{
		grid.swapBlock(x, y - 1, this, x, y);
		setUpdate(true);
		grid.getBlock(x, y - 1)->setUpdate(true);
		return ;
	}

	// Security & Movement
	const bool	leftFirst = std::rand() % 2;

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
