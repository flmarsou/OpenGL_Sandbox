#pragma once

# include "debug.hpp"
# include <iostream>
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
		static bool			_initBuffers;
		static unsigned int	_VAO;	// Vertex Array Object
		static unsigned int	_VBO;	// Vertex Buffer Object
		static unsigned int	_EBO;	// Element Buffer Object
		static bool			_destroyBuffers;

		glm::vec3	_blockColor;
};
