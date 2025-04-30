#pragma once

# include "ABlock.hpp"
# include <vector>
# include <cstdlib>
# include <ctime>

class	ABlock;

class	Grid
{
	public:
		Grid(unsigned int size);
		~Grid();

		void	setBlock(int x, int y, ABlock *block);
		ABlock	*getBlock(int x, int y) const;
		int		getSize() const;

		void	draw(unsigned int &shader);
		void	update();
		int		bound(unsigned int x, unsigned int y);

	private:
		int									_gridSize;
		std::vector<std::vector<ABlock *>>	_grid;
};
