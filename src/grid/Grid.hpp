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

		int		getSize() const;
		ABlock	*getBlock(int x, int y) const;
		void	setBlock(int x, int y, ABlock *block);

		void	draw(unsigned int &shader);
		void	update();
		int		bound(unsigned int x, unsigned int y);

	private:
		int									_gridSize;
		std::vector<std::vector<ABlock *>>	_grid;
};
