#pragma once

# include "IBlock.hpp"

class	Grid
{
	public:
		static const unsigned int gridWidth = 100;
		static const unsigned int gridHeight = 100;

		Grid();
		~Grid();

		IBlock	*getBlock(unsigned int x, unsigned int y) const;
		void	setBlock(unsigned int x, unsigned int y, IBlock *block);

		void	updateGrid();
		void	renderGrid();

	private:
		bool	isInBound(unsigned int x, unsigned int y) const;

		IBlock	*grid[gridHeight][gridWidth];
};
