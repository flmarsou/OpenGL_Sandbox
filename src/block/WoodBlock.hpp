#pragma once

# include "ABlock.hpp"
# include "FireBlock.hpp"

class	WoodBlock : public ABlock
{
	public:
		WoodBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		bool	_burned;
};
