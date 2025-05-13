#pragma once

# include "ABlock.hpp"
# include "FireBlock.hpp"
# include "AshBlock.hpp"

class	WoodBlock : public ABlock
{
	public:
		WoodBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		void	checkSurrounding(Grid &grid, const int x, const int y);
		bool	_burning;
};
