#include "MetalBlock.hpp"

MetalBlock::MetalBlock()
	:	_hasBattery(false)
{
	setId(METAL_BLOCK);

	offColor();
}

ABlock	*MetalBlock::clone() const
{
	return (new MetalBlock());
}

// ========================================================================== //
//   Colors                                                                   //
// ========================================================================== //

void	MetalBlock::offColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.145f, 0.845f, 0.845f});
			break ;
		case (1):
			setColor({0.105f, 0.805f, 0.805f});
			break ;
		case (2):
			setColor({0.166f, 0.766f, 0.766f});
			break ;
		case (3):
			setColor({0.125f, 0.725f, 0.725f});
			break ;
		default:
			setColor({0.178f, 0.678f, 0.678f});
			break ;
	}
}

void	MetalBlock::onColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			setColor({0.145f, 0.845f, 0.045f});
			break ;
		case (1):
			setColor({0.105f, 0.805f, 0.005f});
			break ;
		case (2):
			setColor({0.166f, 0.766f, 0.066f});
			break ;
		case (3):
			setColor({0.125f, 0.725f, 0.025f});
			break ;
		default:
			setColor({0.178f, 0.678f, 0.078f});
			break ;
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
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == METAL_BLOCK && !grid.getBlock(x, y + 1)->getElec())	// Bottom
		floodFillOn(grid, x, y + 1);
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == METAL_BLOCK && !grid.getBlock(x - 1, y)->getElec())	// Left
		floodFillOn(grid, x - 1, y);
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == METAL_BLOCK && !grid.getBlock(x + 1, y)->getElec())	// Right
		floodFillOn(grid, x + 1, y);
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == METAL_BLOCK && !grid.getBlock(x, y - 1)->getElec())	// Top
		floodFillOn(grid, x, y - 1);
}

void	MetalBlock::floodFillOff(const Grid &grid, const int x, const int y)
{
	grid.getBlock(x, y)->setElec(false);
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getId() == METAL_BLOCK && grid.getBlock(x, y + 1)->getElec())	// Bottom
		floodFillOff(grid, x, y + 1);
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getId() == METAL_BLOCK && grid.getBlock(x - 1, y)->getElec())	// Left
		floodFillOff(grid, x - 1, y);
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getId() == METAL_BLOCK && grid.getBlock(x + 1, y)->getElec())	// Right
		floodFillOff(grid, x + 1, y);
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getId() == METAL_BLOCK && grid.getBlock(x, y - 1)->getElec())	// Top
		floodFillOff(grid, x, y - 1);
}

# include <iostream>

void	MetalBlock::update(Grid &grid, const int x, const int y)
{
	if (!grid.getBlock(x, y)->getElec() && checkBatteries(grid, x, y))
	{
		this->_hasBattery = true;
		floodFillOn(grid, x, y);
	}


	if (grid.getBlock(x, y)->getElec())
		onColor();
	else
		offColor();
}
