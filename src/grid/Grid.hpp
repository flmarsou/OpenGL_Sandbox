#pragma once

# include "Block.hpp"
# include <vector>
# include <cstdlib>
# include <ctime>

class	Grid
{
	public:
		Grid(unsigned int size);
		~Grid();

		void	setBlock(unsigned int cellX, unsigned int cellY, Block *block);

		void	draw(unsigned int &shader);
		void	update();
		int		bound(unsigned int x, unsigned int y);

	private:
		unsigned int						_gridSize;
		std::vector<std::vector<Block *>>	_grid;
};
