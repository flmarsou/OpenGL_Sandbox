#pragma once

# include "ABlock.hpp"

class	ALiquid : public ABlock
{
	protected:
		bool	swapAbove(Grid &grid, const int x, const int y);
		bool	groundMovements(Grid &grid, const int x, const int y);
		bool	diagonalMovements(Grid &grid, const int x, const int y);
};
