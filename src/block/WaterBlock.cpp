#include "WaterBlock.hpp"

WaterBlock::WaterBlock()
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

void	WaterBlock::draw(float posX, float posY, float scale, unsigned int &shader) const
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
	glBindVertexArray(ABlock::_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void	WaterBlock::update(Grid &grid, int x, int y)
{
	// TODO
}
