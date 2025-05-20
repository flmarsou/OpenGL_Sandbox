#pragma once

# include "ALiquid.hpp"

class	WaterBlock : public ALiquid
{
	public:
		WaterBlock();

		ABlock*	clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
