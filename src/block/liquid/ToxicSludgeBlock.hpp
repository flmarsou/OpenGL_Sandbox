#pragma once

# include "ABlock.hpp"

class	ToxicSludgeBlock : public ABlock
{
	public:
		ToxicSludgeBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		void	convertSurrounding(Grid &grid, const int x, const int y);
};
