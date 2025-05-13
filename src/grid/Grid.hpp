#pragma once

# include "ABlock.hpp"
# include <vector>
# include <cstdlib>
# include <ctime>

class	ABlock;

class	Grid
{
	public:
		Grid(const unsigned int size);
		~Grid();

		void	setBlock(const int x, const int y, ABlock *block);
		ABlock	*getBlock(const int x, const int y) const;
		void	swapBlock(const int x, const int y, ABlock *swapBlock, const int swapX, const int swapY);
		void	convertBlock(const int x, const int y, ABlock *convertBlock);
		void	deleteBlock(const int x, const int y);
		int		getSize() const;

		void	draw(const unsigned int shader);
		void	update();

	private:
		int									_gridSize;
		std::vector<std::vector<ABlock *>>	_grid;
};
