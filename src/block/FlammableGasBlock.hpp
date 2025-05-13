#pragma once

# include "ABlock.hpp"

class	FlammableGasBlock : public ABlock
{
	public:
		FlammableGasBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
