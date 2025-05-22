#include "AElectricity.hpp"

bool	AElectricity::checkElectricity(const Grid &grid, const int x, const int y) const
{
	// Top
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getElec())
		return (true);
	// Left
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getElec())
		return (true);
	// Right
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getElec())
		return (true);
	// Bottom
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getElec())
		return (true);

	return (false);
}
