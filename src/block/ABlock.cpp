#include "ABlock.hpp"

bool			ABlock::_initBuffers = false;
unsigned int	ABlock::_VAO = 0;
unsigned int	ABlock::_VBO = 0;
unsigned int	ABlock::_EBO = 0;
bool			ABlock::_destroyBuffers = false;

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

ABlock::ABlock()
{
	// Initializes the VAO, VBO, and EBO (only once)
	if (!_initBuffers)
	{
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

		std::cout << INFO "VAO, VBO, and EBO linked to ABlock!" << std::endl;
		_initBuffers = true;
	}
}

ABlock::~ABlock()
{
	if (!_destroyBuffers)
	{
		glDeleteVertexArrays(1, &_VAO);
		glDeleteBuffers(1, &_VBO);
		glDeleteBuffers(1, &_EBO);

		std::cout << INFO "VAO, VBO, and EBO deleted from ABlock!" << std::endl;
		_destroyBuffers = true;
	}
}

// ========================================================================== //
//   Getters & Setters                                                        //
// ========================================================================== //

void			ABlock::setUpdate(bool isUpdated)
{
	this->_isUpdated = isUpdated;
}

bool			ABlock::getUpdate() const
{
	return (this->_isUpdated);
}

void			ABlock::setId(unsigned int id)
{
	this->_id = id;
}

unsigned int	ABlock::getId()
{
	return (this->_id);
}
