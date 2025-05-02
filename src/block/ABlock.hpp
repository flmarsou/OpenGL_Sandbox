#pragma once

# include "debug.hpp"
# include "Grid.hpp"

# include <iostream>

# include <GLAD/glad.h>

# include <GLM/glm.hpp>
# include <GLM/gtc/matrix_transform.hpp>
# include <GLM/gtc/type_ptr.hpp>

enum	blockType
{
	SANDBLOCK,
	WATERBLOCK
};

class	Grid;

class	ABlock
{
	public:
		ABlock();
		virtual ~ABlock();

		virtual void	draw(float x, float y, float scale, unsigned int &shader) const = 0;
		virtual void	update(Grid &grid, int x, int y) = 0;

		void			setUpdate(bool isUpdated);
		bool			getUpdate() const;
		void			setId(unsigned int id);
		unsigned int	getId();

	protected:
		static unsigned int	_VAO;	// Vertex Array Object
		unsigned int		_id = 0;

	private:
		static bool			_initBuffers;
		static unsigned int	_VBO;	// Vertex Buffer Object
		static unsigned int	_EBO;	// Element Buffer Object
		static bool			_destroyBuffers;
		bool				_isUpdated = false;
};
