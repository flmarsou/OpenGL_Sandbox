#include "MetalBlock.hpp"

MetalBlock::MetalBlock()
	:	_defaultColor(colorOff())
{
	setId(METAL_BLOCK);

	setColor(this->_defaultColor);
}

ABlock	*MetalBlock::clone() const
{
	return (new MetalBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

glm::vec3	MetalBlock::colorOff()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			return {0.78f, 0.78f, 0.80f};
		case (1):
			return {0.70f, 0.72f, 0.75f};
		case (2):
			return {0.62f, 0.64f, 0.68f};
		case (3):
			return {0.55f, 0.57f, 0.60f};
		default:
			return {0.48f, 0.50f, 0.53f};
	}
}

glm::vec3	MetalBlock::colorOn()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			return {0.85f, 0.82f, 0.70f};
		case (1):
			return {0.78f, 0.76f, 0.65f};
		case (2):
			return {0.70f, 0.68f, 0.58f};
		case (3):
			return {0.62f, 0.60f, 0.52f};
		default:
			return {0.55f, 0.53f, 0.45f};
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

bool	MetalBlock::checkBatteries(const Grid &grid, const int x, const int y)
{
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == BATTERY_BLOCK)
		return (true);
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == BATTERY_BLOCK)
		return (true);
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == BATTERY_BLOCK)
		return (true);
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == BATTERY_BLOCK)
		return (true);
	return (false);
}

void	MetalBlock::floodFill(const Grid &grid, const int x, const int y)
{
	grid.getBlock(x, y)->setElec(true);
	grid.getBlock(x, y)->setColor(colorOn());
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == METAL_BLOCK && !grid.getBlock(x, y + 1)->getElec())	// Bottom
		floodFill(grid, x, y + 1);
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == METAL_BLOCK && !grid.getBlock(x - 1, y)->getElec())	// Left
		floodFill(grid, x - 1, y);
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == METAL_BLOCK && !grid.getBlock(x + 1, y)->getElec())	// Right
		floodFill(grid, x + 1, y);
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == METAL_BLOCK && !grid.getBlock(x, y - 1)->getElec())	// Top
		floodFill(grid, x, y - 1);
}

void	MetalBlock::update(Grid &grid, const int x, const int y)
{
	if (checkBatteries(grid, x, y))
		floodFill(grid, x, y);

	if (!grid.getBlock(x, y)->getElec())
		setColor(this->_defaultColor);
}
