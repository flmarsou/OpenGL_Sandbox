#pragma once

# include "ABlock.hpp"

class	AshBlock : public ABlock
{
	public:
		AshBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
