#include "Grid.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

Grid::Grid(const unsigned int size)
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

void	Grid::setBlock(const int x, const int y, ABlock *block)
{
	if (x < 0 || x >= this->_gridSize || y < 0 || y >= this->_gridSize || (block && this->_grid[y][x]))
		return ;
	this->_grid[y][x] = block;
}

ABlock	*Grid::getBlock(const int x, const int y) const
{
	if (x < 0 || x >= this->_gridSize || y < 0 || y >= this->_gridSize || !this->_grid[y][x])
		return (nullptr);
	return (this->_grid[y][x]);
}

void	Grid::swapBlock(const int originX, const int originY, ABlock *swapBlock, const int swapX, const int swapY)
{
	ABlock	*temp;
	temp = this->_grid[originY][originX];
	if (temp)
	{
		this->_grid[originY][originX] = swapBlock;
		this->_grid[swapY][swapX] = temp;
	}
}

int		Grid::getSize() const
{
	return (this->_gridSize);
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	Grid::draw(const unsigned int &shader)
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
	for (int y = 0; y < this->_gridSize; y++)
		for (int x = 0; x < this->_gridSize; x++)
			if (this->_grid[y][x])
				this->_grid[y][x]->setUpdate(false);

	for (int y = 0; y < this->_gridSize; y++)
		for (int x = 0; x < this->_gridSize; x++)
			if (this->_grid[y][x] && !this->_grid[y][x]->getUpdate())
				this->_grid[y][x]->update(*this, x, y);
}
