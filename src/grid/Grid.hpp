#pragma once

# include "Block.hpp"
# include <vector>
# include <cstdlib>
# include <ctime>

class	Grid
{
	public:
		Grid(unsigned int sizeX, unsigned int sizeY);

		void	setBlock(unsigned int cellX, unsigned int cellY, Block *block);

		void	draw(unsigned int &shader);
		void	update();
		int		bound(unsigned int x, unsigned int y);

	private:
		float								cellSize;
		std::vector<std::vector<Block *>>	grid;
};
