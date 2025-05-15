#pragma once

# include "ABlock.hpp"

class	WaterBlock : public ABlock
{
	public:
		WaterBlock();

		ABlock*	clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		bool	convertSurrounding(Grid &grid, const int x, const int y);
};
