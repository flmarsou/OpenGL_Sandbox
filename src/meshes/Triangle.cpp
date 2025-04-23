#include "Triangle.hpp"

Triangle::Triangle()
{
	const float	vertices[] = {
		//  x, y, r, g, b
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	// Bottom Left
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	// Bottom Right
		 0.0f,  0.5f, 0.0f, 0.0f, 1.0f	// Top
	};

	// Array Buffer
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// Vertex Buffer
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

Triangle::~Triangle()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void	Triangle::draw() const
{
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
