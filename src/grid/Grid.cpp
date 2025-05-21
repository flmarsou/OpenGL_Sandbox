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
			setBlock(dx, dy, newBlock);
		}
	}
	delete block;
}

void	Grid::erase(const int x, const int y, int cursorSize)
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

			deleteBlock(dx, dy);
		}
	}
}

void Grid::draw(const unsigned int shader)
{
	std::vector<glm::mat4> transforms;
	std::vector<glm::vec3> colors;

	const float cellSizeNDC = 2.0f / this->_gridSize;

	for (int y = 0; y < this->_gridSize; y++)
		for (int x = 0; x < this->_gridSize; x++)
		{
			if (this->_grid[y][x])
			{
				float ndcX = -1.0f + (x * cellSizeNDC);
				float ndcY =  1.0f - ((y + 1) * cellSizeNDC);

				glm::mat4 transform = glm::mat4(1.0f);
				transform = glm::translate(transform, glm::vec3(ndcX, ndcY, 0.0f));
				transform = glm::scale(transform, glm::vec3(cellSizeNDC, cellSizeNDC, 1.0f));

				transforms.push_back(transform);
				colors.push_back(this->_grid[y][x]->getColor());
			}
		}

	ABlock::drawInstanced(transforms, colors, shader);
}

void	Grid::update()
{
	// Reset blocks (expect for batteries' electricity)
	for (int y = 0; y < this->_gridSize; y++)
		for (int x = 0; x < this->_gridSize; x++)
			if (this->_grid[y][x])
			{
				this->_grid[y][x]->setUpdate(false);
				if (getBlock(x, y)->getId() != BATTERY_BLOCK)
					this->_grid[y][x]->setElec(false);
			}

	// Update BatteryBlock and MetalBlock
	for (int y = this->_gridSize - 1; y >= 0; y--)
		for (int x = this->_gridSize - 1; x >= 0; x--)
			if (this->_grid[y][x] && (this->_grid[y][x]->getId() == BATTERY_BLOCK || this->_grid[y][x]->getId() == METAL_BLOCK))
				this->_grid[y][x]->update(*this, x, y);

	// Update Blocks
	for (int y = this->_gridSize - 1; y >= 0; y--)
	{
		// Left to Right
		if (y % 2)
		{
			for (int x = this->_gridSize - 1; x >= 0; x--)
				if (this->_grid[y][x] && !this->_grid[y][x]->getUpdate())
					this->_grid[y][x]->update(*this, x, y);
		}
		// Right to Left
		else
		{
			for (int x = 0; x < this->_gridSize; x++)
				if (this->_grid[y][x] && !this->_grid[y][x]->getUpdate())
					this->_grid[y][x]->update(*this, x, y);
		}
	}
}
