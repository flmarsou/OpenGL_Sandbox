#pragma once

# include "ABlock.hpp"

class	WaterBlock : public ABlock
{
	public:
		WaterBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
