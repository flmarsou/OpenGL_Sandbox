#include "AcidBlock.hpp"
#include "ToxicSludgeBlock.hpp"

AcidBlock::AcidBlock()
{
	setId(ACID_BLOCK);
	setType(LIQUID_TYPE);

	randomizeColor();
}

ABlock	*AcidBlock::clone() const
{
	return (new AcidBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	AcidBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): setColor({0.102f, 0.722f, 0.290f}); break ;
		case (1): setColor({0.102f, 0.690f, 0.290f}); break ;
		case (2): setColor({0.102f, 0.659f, 0.290f}); break ;
		case (3): setColor({0.102f, 0.627f, 0.290f}); break ;
		default: setColor({0.102f, 0.596f, 0.290f}); break ;
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static bool	dissolveChances(Grid &grid, const int x, const int y)
{
	const unsigned int	id = grid.getBlock(x, y)->getId();

	// 100%
	if (id == SAND_BLOCK
		|| id == ASH_BLOCK
		|| id == WOOD_BLOCK
		|| id == TOXIC_SLUDGE_BLOCK
		|| id == MUD_BLOCK
		|| id == RED_LED_BLOCK
		|| id == GREEN_LED_BLOCK
		|| id == BLUE_LED_BLOCK
		|| id == C4_BLOCK
		|| id == OIL_BLOCK)
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

	// 1%
	if (std::rand() % 100 < 1 && (id == METAL_BLOCK || id == BATTERY_BLOCK))
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

static bool	dissolveSurrounding(Grid &grid, const int x, const int y)
{
	bool				dissolved = false;

	// Skip chance
	if (std::rand() % 100 < 75)
		return (false);

	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() != ACID_BLOCK)
		dissolved = dissolveChances(grid, x, y - 1);
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() != ACID_BLOCK)
		dissolved = dissolveChances(grid, x - 1, y);
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() != ACID_BLOCK)
		dissolved = dissolveChances(grid, x + 1, y);
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() != ACID_BLOCK)
		dissolved = dissolveChances(grid, x, y + 1);

	// Kills the acid block if it dissolved something with 50% chance
	if (dissolved && std::rand() % 2)
		return (true);

	return (false);
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
	if (dissolveSurrounding(grid, x, y))
	{
		grid.deleteBlock(x, y);
		return ;
	}

	// Movements
	if (swapAbove(grid, x, y))
		return ;
	if (groundMovements(grid, x, y))
		return ;
	if (fallDown(grid, x, y))
		return ;
	if (diagonalMovements(grid, x, y))
		return ;
}
