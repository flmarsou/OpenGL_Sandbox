#pragma once

# include "ABlock.hpp"
# include "FireBlock.hpp"

class	FlammableGasBlock : public ABlock
{
	public:
		FlammableGasBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		void	checkSurrounding(Grid &grid, const int x, const int y);

		bool	_burning;
};
