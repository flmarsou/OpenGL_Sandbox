#pragma once

# include "ABlock.hpp"

class	AElectricity : public ABlock
{
	protected:
		bool	checkElectricity(const Grid &grid, const int x, const int y) const;
};
