#include "SandBlock.hpp"

SandBlock::SandBlock()
{
	const float	quadVertices[] = {
		// Pos (x, y)		Color (r, g, b)
		 0.0f,  0.0f,		0.9f, 0.8f, 0.2f,	// Bottom-Left
		 1.0f,  0.0f,		0.9f, 0.8f, 0.2f,	// Bottom-Right
		 1.0f,  1.0f,		0.9f, 0.8f, 0.2f,	// Top-Right

		 1.0f,  1.0f,		0.9f, 0.8f, 0.2f,	// Top-Right
		 0.0f,  1.0f,		0.9f, 0.8f, 0.2f,	// Top-Left
		 0.0f,  0.0f,		0.9f, 0.8f, 0.2f,	// Bottom-Left
	};

	// Array Buffer
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// Vertex Buffer
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	// Vertex Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// Vertex Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

SandBlock::~SandBlock()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void	SandBlock::drawBlock(unsigned int x, unsigned int y) const
{
	(void)x;
	(void)y;
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
