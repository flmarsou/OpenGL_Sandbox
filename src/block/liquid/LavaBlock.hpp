#pragma once

# include "ALiquid.hpp"

class	LavaBlock : public ALiquid
{
	public:
		LavaBlock();

		ABlock*	clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
