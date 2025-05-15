#pragma once

# include "ABlock.hpp"
# include "FireBlock.hpp"

class	BombBlock : public ABlock
{
	public:
		BombBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;
};
