#include "IceBlock.hpp"
#include "WaterBlock.hpp"

IceBlock::IceBlock()
{
	setId(ICE_BLOCK);

	randomizeColor();
}

ABlock	*IceBlock::clone() const
{
	return (new IceBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	IceBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.75f, 0.90f, 1.0f}); break ;
		case (1): setColor({0.65f, 0.85f, 0.95f}); break ;
		case (2): setColor({0.80f, 0.95f, 1.0f}); break ;
		case (3): setColor({0.70f, 0.88f, 0.98f}); break ;
		default: setColor({0.60f, 0.80f, 0.95f}); break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static bool	checkFire(Grid &grid, const int x, const int y)
{
	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x, y, new WaterBlock());
		return (true);
	}
	// Top Left
	if (grid.getBlock(x - 1, y - 1) && grid.getBlock(x - 1, y - 1)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x, y, new WaterBlock());
		return (true);
	}
	// Top Right
	if (grid.getBlock(x + 1, y - 1) && grid.getBlock(x + 1, y - 1)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x, y, new WaterBlock());
		return (true);
	}
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x, y, new WaterBlock());
		return (true);
	}
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x, y, new WaterBlock());
		return (true);
	}
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x, y, new WaterBlock());
		return (true);
	}
	// Bottom Left
	if (grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x, y, new WaterBlock());
		return (true);
	}
	// Bottom Right
	if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getId() == FIRE_BLOCK)
	{
		grid.convertBlock(x, y, new WaterBlock());
		return (true);
	}
	return (false);
}

static void	checkWater(Grid &grid, const int x, const int y)
{
	// Skip chance
	if (std::rand() % 1000 != 1)
		return ;

	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == WATER_BLOCK)
		grid.convertBlock(x, y - 1, new IceBlock());
	// Top Left
	if (grid.getBlock(x - 1, y - 1) && grid.getBlock(x - 1, y - 1)->getId() == WATER_BLOCK)
		grid.convertBlock(x - 1, y - 1, new IceBlock());
	// Top Right
	if (grid.getBlock(x + 1, y - 1) && grid.getBlock(x + 1, y - 1)->getId() == WATER_BLOCK)
		grid.convertBlock(x + 1, y - 1, new IceBlock());
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == WATER_BLOCK)
		grid.convertBlock(x - 1, y, new IceBlock());
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == WATER_BLOCK)
		grid.convertBlock(x + 1, y, new IceBlock());
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == WATER_BLOCK)
		grid.convertBlock(x, y + 1, new IceBlock());
	// Bottom Left
	if (grid.getBlock(x - 1, y + 1) && grid.getBlock(x - 1, y + 1)->getId() == WATER_BLOCK)
		grid.convertBlock(x - 1, y + 1, new IceBlock());
	// Bottom Right
	if (grid.getBlock(x + 1, y + 1) && grid.getBlock(x + 1, y + 1)->getId() == WATER_BLOCK)
		grid.convertBlock(x + 1, y + 1, new IceBlock());
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	IceBlock::update(Grid &grid, const int x, const int y)
{
	if (checkFire(grid, x, y))
		return ;

	checkWater(grid, x, y);
}
