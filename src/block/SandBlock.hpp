#pragma once

# include "IBlock.hpp"

# include <GLAD/glad.h>

class	SandBlock : public IBlock
{
	public:
		SandBlock();
		~SandBlock();

		void	drawBlock(unsigned int x, unsigned int y) const;

	private:
		unsigned int	VBO;	// Vertex Buffer Object
		unsigned int	VAO;	// Vertex Array Object
		unsigned int	EBO;	// Element Buffer Object
};
