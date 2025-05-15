#include "Grid.hpp"
#include "debug.hpp"

#include <ctime>

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

Grid::Grid(const unsigned int size)
{
	this->_grid.resize(size, std::vector<ABlock *>(size, nullptr));
	this->_gridSize = size;
	std::cout << SUCCESS "Grid initialized!" << std::endl;
}
Grid::~Grid()
{
	for (int y = 0; y < this->_gridSize; y++)
		for (int x = 0; x < this->_gridSize; x++)
			if (this->_grid[y][x])
				delete this->_grid[y][x];
}

// ========================================================================== //
//   Getters & Setters                                                        //
// ========================================================================== //

void	Grid::setBlock(const int x, const int y, ABlock *block)
{
	if (x < 0 || x >= this->_gridSize || y < 0 || y >= this->_gridSize || (block && this->_grid[y][x]))
	{
		delete block;
		return ;
	}
	this->_grid[y][x] = block;
}

ABlock	*Grid::getBlock(const int x, const int y) const
{
	if (x < 0 || x >= this->_gridSize || y < 0 || y >= this->_gridSize || !this->_grid[y][x])
		return (nullptr);
	return (this->_grid[y][x]);
}

void	Grid::swapBlock(const int x, const int y, ABlock *swapBlock, const int swapX, const int swapY)
{
	ABlock	*temp = this->_grid[y][x];

	if (temp)
	{
		this->_grid[y][x] = swapBlock;
		this->_grid[swapY][swapX] = temp;
	}
}

void	Grid::convertBlock(const int x, const int y, ABlock *convertBlock)
{
	ABlock	*temp = this->_grid[y][x];

	if (temp)
		deleteBlock(x, y);
	setBlock(x, y, convertBlock);
}

void	Grid::deleteBlock(const int x, const int y)
{
	if (!(x < 0 || x >= this->_gridSize || y < 0 || y >= this->_gridSize) && this->_grid[y][x])
	{
		delete this->_grid[y][x];
		this->_grid[y][x] = nullptr;
	}
}

int		Grid::getSize() const
{
	return (this->_gridSize);
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	Grid::place(const int x, const int y, ABlock *block, int cursorSize)
{
	const int	radius = cursorSize - 1;

	for (int offsetY = -radius; offsetY <= radius; offsetY++)
	{
		for (int offsetX = -radius; offsetX <= radius; offsetX++)
		{
			int	dx = x + offsetX;
			int dy = y + offsetY;

			if (offsetX * offsetX + offsetY * offsetY > radius * radius)
				continue ;

			ABlock	*newBlock = block->clone();
			this->setBlock(dx, dy, newBlock);
		}
	}
	delete block;
}

void	Grid::draw(const unsigned int shader)
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

	for (int y = this->_gridSize - 1; y >= 0; y--)
		for (int x = this->_gridSize - 1; x >= 0; x--)
			if (this->_grid[y][x] && !this->_grid[y][x]->getUpdate())
				this->_grid[y][x]->update(*this, x, y);
}
