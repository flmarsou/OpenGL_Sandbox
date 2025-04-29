#include "Grid.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

Grid::Grid(unsigned int sizeX, unsigned int sizeY)
{
	this->grid.resize(sizeY, std::vector<Block *>(sizeX, nullptr));
	this->cellSize = 10;
	std::srand(std::time(NULL));
}

Grid::~Grid()
{
	// Delete Blocks
}

// ========================================================================== //
//   Getters & Setters                                                        //
// ========================================================================== //

void	Grid::setBlock(unsigned int cellX, unsigned int cellY, Block *block)
{
	if (!this->grid[cellY][cellX])
		this->grid[cellY][cellX] = block;
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	Grid::draw(unsigned int &shader)
{
	for (unsigned int y = 0; y < this->grid.size(); y++)
		for (unsigned int x = 0; x < this->grid[y].size(); x++)
			if (this->grid[y][x])
			{
				float cellSizeNDC = 2.0f / 100;
				float ndcX = -1.0f + (x * cellSizeNDC);
				float ndcY =  1.0f - ((y + 1) * cellSizeNDC);

				this->grid[y][x]->draw(ndcX, ndcY, cellSizeNDC, shader);
			}
}

void	Grid::update()
{
	for (unsigned int y = 98; y > 0; y--)
		for (unsigned int x = 98; x > 0; x--)
			if (this->grid[y][x])
			{
				switch (bound(x, y))
				{
					case (0):
					{
						const unsigned int	chance = std::rand() % 100;
						if (chance <= 80)
						{
							if (chance < 40 && !this->grid[y + 1][x + 1])
							{
								this->grid[y + 1][x + 1] = this->grid[y][x];
								this->grid[y][x] = nullptr;
							}
							else if (!this->grid[y + 1][x - 1])
							{
								this->grid[y + 1][x - 1] = this->grid[y][x];
								this->grid[y][x] = nullptr;
							}
						}
						break ;
					}
					case (1):
					{
						this->grid[y + 1][x] = this->grid[y][x];
						this->grid[y][x] = nullptr;
						break ;
					}
					default:
						break ;
				}
			}
}

int		Grid::bound(unsigned int x, unsigned int y)
{
	if (this->grid[y + 1][x])
		return (0);
	if (y <= 98)
		return (1);
	return (2);
}
