#pragma once

# include "ABlock.hpp"

class	AGas : public ABlock
{
	protected:
		bool	swapAbove(Grid &grid, const int x, const int y);
		bool	blockedMovements(Grid &grid, const int x, const int y);
		bool	risingMovements(Grid &grid, const int x, const int y);
};
