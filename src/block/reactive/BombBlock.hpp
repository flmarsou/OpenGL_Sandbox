#pragma once

# include "ABlock.hpp"
# include "FireBlock.hpp"

class	BombBlock : public ABlock
{
	public:
		BombBlock();

		void	update(Grid &grid, const int x, const int y) override;
};
