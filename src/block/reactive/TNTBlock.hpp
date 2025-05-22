#pragma once

# include "ABlock.hpp"

class	TNTBlock : public ABlock
{
	public:
		TNTBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
