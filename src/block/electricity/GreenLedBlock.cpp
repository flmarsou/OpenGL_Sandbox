#include "GreenLedBlock.hpp"

GreenLedBlock::GreenLedBlock()
	:	_defaultColor(colorOff())
{
	setId(GREEN_LED_BLOCK);
	setType(ELECTRICITY_TYPE);

	setColor(this->_defaultColor);
}

ABlock	*GreenLedBlock::clone() const
{
	return (new GreenLedBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

const glm::vec3	GreenLedBlock::colorOn() const
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): return {0.3f, 1.0f, 0.3f};
		case (1): return {0.25f, 0.95f, 0.25f};
		case (2): return {0.2f, 0.9f, 0.2f};
		case (3): return {0.35f, 1.0f, 0.35f};
		default: return {0.2f, 0.85f, 0.2f};
	}
}

const glm::vec3	GreenLedBlock::colorOff() const
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0): return {0.05f, 0.2f, 0.05f};
		case (1): return {0.04f, 0.15f, 0.04f};
		case (2): return {0.03f, 0.1f, 0.03f};
		case (3): return {0.06f, 0.25f, 0.06f};
		default: return {0.05f, 0.18f, 0.05f};
	}
}

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

void	GreenLedBlock::floodFill(const Grid &grid, const int x, const int y) const
{
	grid.getBlock(x, y)->setElec(true);
	grid.getBlock(x, y)->setColor(colorOn());

	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == GREEN_LED_BLOCK && !grid.getBlock(x, y - 1)->getElec())
		floodFill(grid, x, y - 1);
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == GREEN_LED_BLOCK && !grid.getBlock(x - 1, y)->getElec())
		floodFill(grid, x - 1, y);
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == GREEN_LED_BLOCK && !grid.getBlock(x + 1, y)->getElec())
		floodFill(grid, x + 1, y);
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == GREEN_LED_BLOCK && !grid.getBlock(x, y + 1)->getElec())
		floodFill(grid, x, y + 1);
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	GreenLedBlock::update(Grid &grid, const int x, const int y)
{
	if (checkElectricity(grid, x, y))
		floodFill(grid, x, y);

	if (!grid.getBlock(x, y)->getElec())
		setColor(this->_defaultColor);
}
