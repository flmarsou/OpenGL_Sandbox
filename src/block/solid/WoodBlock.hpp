#pragma once

# include "ABlock.hpp"

class	WoodBlock : public ABlock
{
	public:
		WoodBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		void	checkSurrounding(Grid &grid, const int x, const int y);
		bool	_burning;
};
