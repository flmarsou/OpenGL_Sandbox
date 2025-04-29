#pragma once

# include <GLAD/glad.h>
# include <GLM/glm.hpp>
# include <GLM/gtc/matrix_transform.hpp>
# include <GLM/gtc/type_ptr.hpp>

class	Block
{
	public:
		Block();
		~Block();

		void	draw(float x, float y, float scale, unsigned int &shader) const;

	private:
		unsigned int	VBO;	// Vertex Buffer Object
		unsigned int	VAO;	// Vertex Array Object
		unsigned int	EBO;	// Element Buffer Object
};
