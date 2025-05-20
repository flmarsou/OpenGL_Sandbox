#include "BatteryBlock.hpp"

BatteryBlock::BatteryBlock()
{
	setId(BATTERY_BLOCK);
	setType(ELECTRICITY_TYPE);
	setElec(true);

	randomizeColor();
}

ABlock	*BatteryBlock::clone() const
{
	return (new BatteryBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	BatteryBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({1.0f, 0.85f, 0.3f});
			break;
		case (1):
			setColor({0.95f, 0.75f, 0.25f});
			break;
		case (2):
			setColor({0.9f, 0.65f, 0.2f});
			break;
		case (3):
			setColor({0.85f, 0.6f, 0.15f});
			break;
		default:
			setColor({0.8f, 0.55f, 0.1f});
			break;
	}
}

// ========================================================================== //
//   Behaviors                                                                //
// ========================================================================== //

void	BatteryBlock::update(Grid &grid, const int x, const int y)
{
	(void)grid;
	(void)x;
	(void)y;
	setUpdate(true);
}
