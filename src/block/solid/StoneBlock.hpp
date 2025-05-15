#pragma once

# include "ABlock.hpp"

class	StoneBlock : public ABlock
{
	public:
		StoneBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
