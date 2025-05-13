#pragma once

# include "ABlock.hpp"

class	StoneBlock : public ABlock
{
	public:
		StoneBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
