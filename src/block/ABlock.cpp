#include "ABlock.hpp"
#include "debug.hpp"

unsigned int	ABlock::_VAO = 0;
unsigned int	ABlock::_VBO = 0;
unsigned int	ABlock::_EBO = 0;
unsigned int	ABlock::_instanceVBO = 0;
unsigned int	ABlock::_colorVBO = 0;

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

	// Creates buffers for instancing
	glGenBuffers(1, &_instanceVBO);
	glGenBuffers(1, &_colorVBO);

	std::cout << SUCCESS "VAO, VBO, EBO, and instances linked to Block!" << std::endl;
}

void	ABlock::deleteBlock()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
}

void	ABlock::drawInstanced(const std::vector<glm::mat4> &transforms, const std::vector<glm::vec3> &colors, unsigned int shader)
{
	glUseProgram(shader);
	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(glm::mat4), transforms.data(), GL_DYNAMIC_DRAW);

	std::size_t vec4Size = sizeof(glm::vec4);
	for (int i = 0; i < 4; i++)
	{
		glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(i * vec4Size));
		glEnableVertexAttribArray(1 + i);
		glVertexAttribDivisor(1 + i, 1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, _colorVBO);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(5, 1);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, transforms.size());
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

glm::vec3		ABlock::getColor() const
{
	return (this->_blockColor);
}

void			ABlock::setId(const unsigned int id)
{
	this->_id = id;
}

unsigned int	ABlock::getId() const
{
	return (this->_id);
}

void			ABlock::setType(const unsigned int type)
{
	this->_type = type;
}

unsigned int	ABlock::getType() const
{
	return (this->_type);
}

void			ABlock::setElec(const bool isElectrified)
{
	this->_isElectrified = isElectrified;
}

bool			ABlock::getElec() const
{
	return (this->_isElectrified);
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

// ===================================== //
//   Movements                           //
// ===================================== //

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

bool	ABlock::riseUp(Grid &grid, const int x, const int y)
{
	if (y > 0 && !grid.getBlock(x, y - 1))
	{
		grid.setBlock(x, y - 1, this);
		grid.setBlock(x, y, nullptr);
		this->_isUpdated = true;
		return (true);
	}
	return (false);
}


bool	ABlock::riseLeft(Grid &grid, const int x, const int y)
{
	if (x > 0 && y > 0 && !grid.getBlock(x - 1, y - 1))
	{
		grid.setBlock(x - 1, y - 1, this);
		grid.setBlock(x, y, nullptr);
		this->_isUpdated = true;
		return (true);
	}
	return (false);
}

bool	ABlock::riseRight(Grid &grid, const int x, const int y)
{
	if (x < grid.getSize() - 1 && y > 0 && !grid.getBlock(x + 1, y - 1))
	{
		grid.setBlock(x + 1, y - 1, this);
		grid.setBlock(x, y, nullptr);
		this->_isUpdated = true;
		return (true);
	}
	return (false);
}
