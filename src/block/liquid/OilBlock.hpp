#pragma once

# include "ALiquid.hpp"

class	OilBlock : public ALiquid
{
	public:
		OilBlock();

		ABlock*	clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		void	checkFire(Grid &grid, const int x, const int y);
		bool	_burning;

		bool	swapLiquids(Grid &grid, const int x, const int y);
		bool	spreadFire(Grid &grid, const int x, const int y);
};
