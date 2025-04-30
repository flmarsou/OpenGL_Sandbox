#include "Grid.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

Grid::Grid(unsigned int size)
{
	this->_grid.resize(size, std::vector<Block *>(size, nullptr));
	this->_gridSize = size;
	std::cout << INFO "Grid initialized!" << std::endl;
}

Grid::~Grid()
{
	for (int y = this->_grid.size() - 1; y >= 0; --y)
		for (int x = this->_grid[y].size() - 1; x >= 0; --x)
			if (this->_grid[y][x])
				delete this->_grid[y][x];
	std::cout << INFO "Grid deleted!" << std::endl;
}

// ========================================================================== //
//   Getters & Setters                                                        //
// ========================================================================== //

void	Grid::setBlock(unsigned int cellX, unsigned int cellY, Block *block)
{
	if (!this->_grid[cellY][cellX])
		this->_grid[cellY][cellX] = block;
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	Grid::draw(unsigned int &shader)
{
	for (unsigned int y = 0; y < this->_grid.size(); y++)
		for (unsigned int x = 0; x < this->_grid[y].size(); x++)
			if (this->_grid[y][x])
			{
				const float	cellSizeNDC = 2.0f / this->_gridSize;
				const float	ndcX = -1.0f + (x * cellSizeNDC);
				const float	ndcY =  1.0f - ((y + 1) * cellSizeNDC);

				this->_grid[y][x]->draw(ndcX, ndcY, cellSizeNDC, shader);
			}
}

void	Grid::update()
{
	for (int y = this->_grid.size() - 1; y >= 0; --y)
		for (int x = this->_grid[y].size() - 1; x >= 0; --x)
			if (this->_grid[y][x])
			{
				switch (bound(x, y))
				{
					case (0):
					{
						const unsigned int	chance = std::rand() % 100;
						if (chance <= 80)
						{
							if (chance < 40 && !this->_grid[y + 1][x + 1])
							{
								this->_grid[y + 1][x + 1] = this->_grid[y][x];
								this->_grid[y][x] = nullptr;
							}
							else if (!this->_grid[y + 1][x - 1])
							{
								this->_grid[y + 1][x - 1] = this->_grid[y][x];
								this->_grid[y][x] = nullptr;
							}
						}
						break ;
					}
					case (1):
					{
						this->_grid[y + 1][x] = this->_grid[y][x];
						this->_grid[y][x] = nullptr;
						break ;
					}
					default:
						break ;
				}
			}
}

int		Grid::bound(unsigned int x, unsigned int y)
{
	if (y + 1 >= this->_grid.size())
		return (-1);
	if (this->_grid[y + 1][x])
		return (0);
	return (1);
}
