#include "WaterBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

WaterBlock::WaterBlock()
{
	setId(WATERBLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	WaterBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			this->_blockColor = {0.102f, 0.518f, 0.722f};	// Very Light Blue
			break ;
		case (1):
			this->_blockColor = {0.102f, 0.549f, 0.722f};	// Light Blue
			break ;
		case (2):
			this->_blockColor = {0.102f, 0.580f, 0.722f};	// Blue
			break ;
		case (3):
			this->_blockColor = {0.102f, 0.611f, 0.722f};	// Dark Blue
			break ;
		default:
			this->_blockColor = {0.102f, 0.643f, 0.722f};	// Very Dark Blue
			break ;
	}
}

void	WaterBlock::draw(float x, float y, float scale, unsigned int &shader) const
{
	glUseProgram(shader);

	// Matrix
	glm::mat4	transform;
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));		// Position
	transform = glm::scale(transform, glm::vec3(scale, scale, 1.0f));	// Size

	// Shader Transform
	const unsigned int	pos = glGetUniformLocation(shader, "transform");
	glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(transform));

	// Shader Color
	const unsigned int	color = glGetUniformLocation(shader, "color");
	glUniform3fv(color, 1, glm::value_ptr(this->_blockColor));

	// Draws
	glBindVertexArray(ABlock::_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void	WaterBlock::update(Grid &grid, int x, int y)
{
	const unsigned int	chance = std::rand() % 100;

	if (chance == 1)
		randomizeColor();

	// Security
	if (y + 1 >= grid.getSize())
	{
		this->setUpdate(true);
		return ;
	}

	// Free Falling
	if (!grid.getBlock(x, y + 1))
	{
		grid.setBlock(x, y + 1, this);
		grid.setBlock(x, y, nullptr);
		this->setUpdate(true);
		return ;
	}
	// Falling & Moving
	else
	{
		if (chance < 50)
		{
			// Falls left
			if (x > 0 && !grid.getBlock(x - 1, y + 1))
			{
				grid.setBlock(x - 1, y + 1, this);
				grid.setBlock(x, y, nullptr);
				this->setUpdate(true);
				return ;
			}
			// Moves left
			else if (x > 0 && !grid.getBlock(x - 1, y))
			{
				grid.setBlock(x - 1, y, this);
				grid.setBlock(x, y, nullptr);
				this->setUpdate(true);
				return ;
			}
			// Falls right
			else if (x < grid.getSize() - 1 && !grid.getBlock(x + 1, y + 1))
			{
				grid.setBlock(x + 1, y + 1, this);
				grid.setBlock(x, y, nullptr);
				this->setUpdate(true);
				return ;
			}
			// Moves right
			else if (x < grid.getSize() - 1 && !grid.getBlock(x + 1, y))
			{
				grid.setBlock(x + 1, y, this);
				grid.setBlock(x, y, nullptr);
				this->setUpdate(true);
				return ;
			}
		}
		else
		{
			// Falls right
			if (x < grid.getSize() - 1 && !grid.getBlock(x + 1, y + 1))
			{
				grid.setBlock(x + 1, y + 1, this);
				grid.setBlock(x, y, nullptr);
				this->setUpdate(true);
				return ;
			}
			// Moves right
			else if (x < grid.getSize() - 1 && !grid.getBlock(x + 1, y))
			{
				grid.setBlock(x + 1, y, this);
				grid.setBlock(x, y, nullptr);
				this->setUpdate(true);
				return ;
			}
			// Falls left
			else if (x > 0 && !grid.getBlock(x - 1, y + 1))
			{
				grid.setBlock(x - 1, y + 1, this);
				grid.setBlock(x, y, nullptr);
				this->setUpdate(true);
				return ;
			}
			// Moves left
			else if (x > 0 && !grid.getBlock(x - 1, y))
			{
				grid.setBlock(x - 1, y, this);
				grid.setBlock(x, y, nullptr);
				this->setUpdate(true);
				return ;
			}
		}
	}

	// Swapping
	if (y > 0)
	{
		ABlock	*temp;
		temp = grid.getBlock(x, y - 1);
		if (temp && temp->getId() == SANDBLOCK)
		{
			grid.setBlockForce(x, y - 1, this);
			grid.setBlockForce(x, y, temp);
			temp->setUpdate(true);
			this->setUpdate(true);
			return ;
		}
	}
}
