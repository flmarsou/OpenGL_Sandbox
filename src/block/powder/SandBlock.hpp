#pragma once

# include "ABlock.hpp"

class	SandBlock : public ABlock
{
	public:
		SandBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
