#include "Grid.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

Grid::Grid()
{
	for (unsigned y = 0; y < gridHeight; y++)
		for (unsigned int x = 0; x < gridWidth; x++)
			this->grid[y][x] = nullptr;
}

Grid::~Grid()
{
	for (unsigned int y = 0; y < gridHeight; y++)
		for (unsigned int x = 0; x < gridWidth; x++)
			if (this->grid[y][x])
				delete (this->grid[y][x]);
}

// ========================================================================== //
//   Getters & Setters                                                        //
// ========================================================================== //

IBlock	*Grid::getBlock(unsigned int x, unsigned int y) const
{
	if (!this->isInBound(x, y))
		return (nullptr);
	return (this->grid[y][x]);
}

void	Grid::setBlock(unsigned int x, unsigned y, IBlock *block)
{
	if (this->isInBound(x, y) && !this->grid[y][x])
		this->grid[y][x] = block;
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	Grid::updateGrid()
{
	
}

void	Grid::renderGrid()
{
	for (unsigned int y = 0; y < gridHeight; y++)
		for (unsigned int x = 0; x < gridWidth; x++)
			if (this->grid[y][x])
				this->grid[y][x]->drawBlock(x, y);
}

bool	Grid::isInBound(unsigned int x, unsigned int y) const
{
	if (x >= 0 && x <= gridWidth && y >= 0 && y <= gridHeight)
		return (true);
	return (false);
}
