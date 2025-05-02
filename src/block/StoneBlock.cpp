#include "StoneBlock.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

StoneBlock::StoneBlock()
{
	setId(STONEBLOCK);

	randomizeColor();
}

// ========================================================================== //
//   Methods & Functions                                                      //
// ========================================================================== //

void	StoneBlock::randomizeColor()
{
	const unsigned int	chance = std::rand() % 5;

	switch (chance)
	{
		case (0):
			this->_blockColor = {0.845f, 0.845f, 0.845f};	// Very Light Gray
			break ;
		case (1):
			this->_blockColor = {0.805f, 0.805f, 0.805f};	// Light Gray
			break ;
		case (2):
			this->_blockColor = {0.766f, 0.766f, 0.766f};	// Gray
			break ;
		case (3):
			this->_blockColor = {0.725f, 0.725f, 0.725f};	// Dark Gray
			break ;
		default:
			this->_blockColor = {0.678f, 0.678f, 0.678f};	// Very Dark Gray
			break ;
	}
}

void	StoneBlock::draw(float x, float y, float scale, unsigned int &shader) const
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

void	StoneBlock::update(Grid &grid, int x, int y)
{
	(void)grid;
	(void)x;
	(void)y;
}
