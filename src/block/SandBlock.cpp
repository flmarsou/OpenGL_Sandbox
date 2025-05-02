#include "SandBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

SandBlock::SandBlock()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			this->_blockColor = {1.0f, 0.905f, 0.631f};	// Very Light Yellow
			break ;
		case (1):
			this->_blockColor = {1.0f, 0.882f, 0.533f};	// Light Yellow
			break ;
		case (2):
			this->_blockColor = {1.0f, 0.859f, 0.439f};	// Yellow
			break ;
		case (3):
			this->_blockColor = {1.0f, 0.835f, 0.341f};	// Dark Yellow
			break ;
		default:
			this->_blockColor = {1.0f, 0.784f, 0.251f};	// Very Dark Yellow
			break ;
	}
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	SandBlock::draw(float x, float y, float scale, unsigned int &shader) const
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

void	SandBlock::update(Grid &grid, int x, int y)
{
	if (y + 1 >= grid.getSize())
	{
		this->setUpdate(true);
		return ;
	}

	// Falls
	if (!grid.getBlock(x, y + 1))
	{
		grid.setBlock(x, y + 1, this);
		grid.setBlock(x, y, nullptr);
	}
	else
	{
		const unsigned int	chance = std::rand() % 100;
		if (chance < 50)
		{
			// Falls left
			if (x > 0 && !grid.getBlock(x - 1, y + 1))
			{
				grid.setBlock(x - 1, y + 1, this);
				grid.setBlock(x, y, nullptr);
			}
			// Falls right
			else if (x < grid.getSize() - 1 && !grid.getBlock(x + 1, y + 1))
			{
				grid.setBlock(x + 1, y + 1, this);
				grid.setBlock(x, y, nullptr);
			}
		}
		else
		{
			// Falls right
			if (x < grid.getSize() - 1 && !grid.getBlock(x + 1, y + 1))
			{
				grid.setBlock(x + 1, y + 1, this);
				grid.setBlock(x, y, nullptr);
			}
			// Falls left
			else if (x > 0 && !grid.getBlock(x - 1, y + 1))
			{
				grid.setBlock(x - 1, y + 1, this);
				grid.setBlock(x, y, nullptr);
			}
		}
	}
	this->setUpdate(true);
}
