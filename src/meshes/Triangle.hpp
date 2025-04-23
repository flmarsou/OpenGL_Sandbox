#pragma once

# include <GLAD/glad.h>

class Triangle
{
	public:
		Triangle();
		~Triangle();

		void	draw() const;

	private:
		unsigned int	VBO;	// Vertex Buffer Object
		unsigned int	VAO;	// Vertex Array Object
};
