#include "ABlock.hpp"

unsigned int	ABlock::_VAO = 0;
unsigned int	ABlock::_VBO = 0;
unsigned int	ABlock::_EBO = 0;

// ========================================================================== //
//   Initializers                                                             //
// ========================================================================== //

void	ABlock::initBlock()
{
	// Initializes the VAO, VBO, and EBO (only once)
	const float			vertices[] = {
		// Pos (x, y)
		0.0f,  0.0f,	// Bottom-Left
		1.0f,  0.0f,	// Bottom-Right
		1.0f,  1.0f,	// Top-Right
		0.0f,  1.0f,	// Top-Left
	};

	const unsigned int	indices[] = {
		// 0 -> Bottom-Left, 1 -> Bottom-Right, 2 -> Top-Right, 3 -> Top-Left
		0, 1, 2,
		0, 2, 3
	};

	// Vertex Array Object
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	// Vertex Buffer Object
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Element Buffer Object
	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Vertex Attribute: Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	std::cout << INFO "VAO, VBO, and EBO linked to Block!" << std::endl;
}

void	ABlock::deleteBlock()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);

	std::cout << INFO "VAO, VBO, and EBO deleted from Block!" << std::endl;
}

// ========================================================================== //
//   Getters & Setters                                                        //
// ========================================================================== //

void			ABlock::setUpdate(const bool isUpdated)
{
	this->_isUpdated = isUpdated;
}

bool			ABlock::getUpdate() const
{
	return (this->_isUpdated);
}

void			ABlock::setColor(const glm::vec3 color)
{
	this->_blockColor = color;
}

void			ABlock::setId(const unsigned int id)
{
	this->_id = id;
}

unsigned int	ABlock::getId() const
{
	return (this->_id);
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	ABlock::draw(const float x, const float y, const float scale, const unsigned int shader) const
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
	glBindVertexArray(this->_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool	ABlock::isOnGround(Grid &grid, const int y)
{
	if (y + 1 >= grid.getSize())
	{
		this->_isUpdated = true;
		return (true);
	}
	return (false);
}

bool	ABlock::fallDown(Grid &grid, const int x, const int y)
{
	if (!grid.getBlock(x, y + 1))
	{
		grid.setBlock(x, y + 1, this);
		grid.setBlock(x, y, nullptr);
		this->_isUpdated = true;
		return (true);
	}
	return (false);
}

bool	ABlock::fallLeft(Grid &grid, const int x, const int y)
{
	if (x > 0 && !grid.getBlock(x - 1, y + 1))
	{
		grid.setBlock(x - 1, y + 1, this);
		grid.setBlock(x, y, nullptr);
		this->_isUpdated = true;
		return (true);
	}
	return (false);
}

bool	ABlock::fallRight(Grid &grid, const int x, const int y)
{
	if (x < grid.getSize() - 1 && !grid.getBlock(x + 1, y + 1))
	{
		grid.setBlock(x + 1, y + 1, this);
		grid.setBlock(x, y, nullptr);
		this->_isUpdated = true;
		return (true);
	}
	return (false);
}

bool	ABlock::moveLeft(Grid &grid, const int x, const int y)
{
	if (x > 0 && !grid.getBlock(x - 1, y))
	{
		grid.setBlock(x - 1, y, this);
		grid.setBlock(x, y, nullptr);
		this->_isUpdated = true;
		return (true);
	}
	return (false);
}

bool	ABlock::moveRight(Grid &grid, const int x, const int y)
{
	if (x < grid.getSize() - 1 && !grid.getBlock(x + 1, y))
	{
		grid.setBlock(x + 1, y, this);
		grid.setBlock(x, y, nullptr);
		this->_isUpdated = true;
		return (true);
	}
	return (false);
}
