#pragma once

# include "ALiquid.hpp"

class	AcidBlock : public ALiquid
{
	public:
		AcidBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		bool	dissolveSurrounding(Grid &grid, const int x, const int y);
		bool	dissolveBehavior(Grid &grid, const int x, const int y);
};
