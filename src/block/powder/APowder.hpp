#pragma once

# include "ABlock.hpp"

class	APowder : public ABlock
{
	protected:
		bool	liquidMovements(Grid &grid, const int x, const int y);
		bool	diagonalMovements(Grid &grid, const int x, const int y);
};
