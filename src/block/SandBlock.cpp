#include "SandBlock.hpp"

SandBlock::SandBlock()
{
	const float			vertices[] = {
		// Pos (x, y)		Color (r, g, b)
		 0.0f,  0.0f,		0.9f, 0.8f, 0.2f,	// Bottom-Left
		 1.0f,  0.0f,		0.9f, 0.8f, 0.2f,	// Bottom-Right
		 1.0f,  1.0f,		0.9f, 0.8f, 0.2f,	// Top-Right
		 0.0f,  1.0f,		0.9f, 0.8f, 0.2f,	// Top-Left
	};

	const unsigned int	indices[] = {
		// 0 -> Bottom-Left, 1 -> Bottom-Right, 2 -> Top-Right, 3 -> Top-Left
		0, 1, 2,
		0, 2, 3
	};

	// Vertex Array Object
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// Vertex Buffer Object
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Element Buffer Object
	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Vertex Attribute: Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// Vertex Attribute: Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

SandBlock::~SandBlock()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void	SandBlock::drawBlock(unsigned int x, unsigned int y) const
{
	(void)x;
	(void)y;
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
