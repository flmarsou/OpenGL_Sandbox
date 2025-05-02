#include "Grid.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

Grid::Grid(unsigned int size)
{
	this->_grid.resize(size, std::vector<ABlock *>(size, nullptr));
	this->_gridSize = size;
	std::cout << INFO "Grid initialized!" << std::endl;
}

Grid::~Grid()
{
	for (int y = this->_gridSize - 1; y >= 0; --y)
		for (int x = this->_gridSize - 1; x >= 0; --x)
			if (this->_grid[y][x])
				delete this->_grid[y][x];
	std::cout << INFO "Grid deleted!" << std::endl;
}

// ========================================================================== //
//   Getters & Setters                                                        //
// ========================================================================== //

void	Grid::setBlock(int x, int y, ABlock *block)
{
	if ((block && this->_grid[y][x]) || x < 0 || x >= this->_gridSize || y < 0 || y >= this->_gridSize)
		return ;
	this->_grid[y][x] = block;
}

void	Grid::setBlockForce(int x, int y, ABlock *block)
{
	if (x < 0 || x >= this->_gridSize || y < 0 || y >= this->_gridSize)
		return ;
	this->_grid[y][x] = block;
}

ABlock	*Grid::getBlock(int x, int y) const
{
	if (x < 0 || x >= this->_gridSize || y < 0 || y >= this->_gridSize || !this->_grid[y][x])
		return (nullptr);
	return (this->_grid[y][x]);
}

int		Grid::getSize() const
{
	return (this->_gridSize);
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	Grid::draw(unsigned int &shader)
{
	for (int y = 0; y < this->_gridSize; y++)
		for (int x = 0; x < this->_gridSize; x++)
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
	for (int y = this->_gridSize - 1; y >= 0; --y)
		for (int x = this->_gridSize - 1; x >= 0; --x)
			if (this->_grid[y][x])
				this->_grid[y][x]->setUpdate(false);

	for (int y = this->_gridSize - 1; y >= 0; --y)
		for (int x = this->_gridSize - 1; x >= 0; --x)
			if (this->_grid[y][x] && !this->_grid[y][x]->getUpdate())
				this->_grid[y][x]->update(*this, x, y);
}
