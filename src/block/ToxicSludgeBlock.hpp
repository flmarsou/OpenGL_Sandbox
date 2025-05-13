#pragma once

# include "ABlock.hpp"
# include "FlammableGasBlock.hpp"

class	ToxicSludgeBlock : public ABlock
{
	public:
		ToxicSludgeBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		void	convertSurrounding(Grid &grid, const int x, const int y);
};
