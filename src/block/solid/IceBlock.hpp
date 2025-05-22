#pragma once

# include "ABlock.hpp"

class	IceBlock : public ABlock
{
	public:
		IceBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
