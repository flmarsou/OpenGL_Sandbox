#include "AElectricity.hpp"

bool	AElectricity::checkElectricity(const Grid &grid, const int x, const int y)
{
	if (grid.getBlock(x, y + 1) && grid.getBlock(x, y + 1)->getElec())
		return (true);
	if (grid.getBlock(x - 1, y) && grid.getBlock(x - 1, y)->getElec())
		return (true);
	if (grid.getBlock(x + 1, y) && grid.getBlock(x + 1, y)->getElec())
		return (true);
	if (grid.getBlock(x, y - 1) && grid.getBlock(x, y - 1)->getElec())
		return (true);
	return (false);
}
