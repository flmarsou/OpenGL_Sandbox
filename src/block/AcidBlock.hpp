#pragma once

# include "ABlock.hpp"

class	AcidBlock : public ABlock
{
	public:
		AcidBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		bool	dissolveSurrounding(Grid &grid, const int x, const int y);
};
