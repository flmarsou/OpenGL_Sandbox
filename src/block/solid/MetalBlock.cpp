#include "MetalBlock.hpp"

MetalBlock::MetalBlock()
	:	_defaultColor(offColor())
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

glm::vec3	MetalBlock::offColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			return {0.6f, 0.6f, 0.65f};
		case (1):
			return {0.5f, 0.55f, 0.6f};
		case (2):
			return {0.55f, 0.55f, 0.58f};
		case (3):
			return {0.52f, 0.57f, 0.63f};
		default:
			return {0.58f, 0.58f, 0.6f};
	}
}

glm::vec3	MetalBlock::onColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			return {0.145f, 0.845f, 0.045f};
		case (1):
			return {0.105f, 0.805f, 0.005f};
		case (2):
			return {0.166f, 0.766f, 0.066f};
		case (3):
			return {0.125f, 0.725f, 0.025f};
		default:
			return {0.178f, 0.678f, 0.078f};
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

void	MetalBlock::floodFillOn(const Grid &grid, const int x, const int y)
{
	grid.getBlock(x, y)->setElec(true);
	grid.getBlock(x, y)->setColor(onColor());
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == METAL_BLOCK && !grid.getBlock(x, y + 1)->getElec())	// Bottom
		floodFillOn(grid, x, y + 1);
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == METAL_BLOCK && !grid.getBlock(x - 1, y)->getElec())	// Left
		floodFillOn(grid, x - 1, y);
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == METAL_BLOCK && !grid.getBlock(x + 1, y)->getElec())	// Right
		floodFillOn(grid, x + 1, y);
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == METAL_BLOCK && !grid.getBlock(x, y - 1)->getElec())	// Top
		floodFillOn(grid, x, y - 1);
}

void	MetalBlock::update(Grid &grid, const int x, const int y)
{
	if (checkBatteries(grid, x, y))
		floodFillOn(grid, x, y);

	if (!grid.getBlock(x, y)->getElec())
		setColor(this->_defaultColor);
}
