#include "Block.hpp"

bool			Block::_initBuffers = false;
unsigned int	Block::_VAO = 0;
unsigned int	Block::_VBO = 0;
unsigned int	Block::_EBO = 0;
bool			Block::_destroyBuffers = false;

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

Block::Block()
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

		std::cout << INFO "VAO, VBO, and EBO linked to Block!" << std::endl;
		_initBuffers = true;
	}

	// Stores a randomly assigned color
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

Block::~Block()
{
	if (!_destroyBuffers)
	{
		glDeleteVertexArrays(1, &_VAO);
		glDeleteBuffers(1, &_VBO);
		glDeleteBuffers(1, &_EBO);

		std::cout << INFO "VAO, VBO, and EBO deleted from Block!" << std::endl;
		_destroyBuffers = true;
	}
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	Block::draw(float posX, float posY, float scale, unsigned int &shader) const
{
	glUseProgram(shader);

	// Matrix
	glm::mat4	transform;
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(posX, posY, 0.0f));	// Position
	transform = glm::scale(transform, glm::vec3(scale, scale, 1.0f));	// Size

	// Shader Transform
	const unsigned int	pos = glGetUniformLocation(shader, "transform");
	glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(transform));

	// Shader Color
	const unsigned int	color = glGetUniformLocation(shader, "color");
	glUniform3fv(color, 1, glm::value_ptr(this->_blockColor));

	// Draws
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
