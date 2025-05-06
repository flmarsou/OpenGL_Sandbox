#pragma once

# include "ABlock.hpp"

class	FireBlock : public ABlock
{
	public:
		FireBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
