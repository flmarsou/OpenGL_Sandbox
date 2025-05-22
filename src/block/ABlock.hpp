#pragma once

# include "enums.hpp"
# include "Grid.hpp"

# include <GLAD/glad.h>
# include <vector>

# include <GLM/glm.hpp>
# include <GLM/gtc/matrix_transform.hpp>
# include <GLM/gtc/type_ptr.hpp>

class	Grid;

class	ABlock
{
	public:
		virtual ~ABlock() {}

		static void	initBlock();
		static void	deleteBlock();
		static void	drawInstanced(const std::vector<glm::mat4> &transforms, const std::vector<glm::vec3> &colors, unsigned int shader);

		virtual void	update(Grid &grid, const int x, const int y) = 0;
		virtual ABlock	*clone() const = 0;

		// Setters & Getters
		void			setUpdate(const bool isUpdated);
		bool			getUpdate() const;

		void			setColor(const glm::vec3 color);
		glm::vec3		getColor() const;

		void			setId(const unsigned int id);
		unsigned int	getId() const;

		void			setType(const unsigned int type);
		unsigned int	getType() const;

		void			setElec(const bool isElectrified);
		bool			getElec() const;

		void			setHot(const bool isHot);
		bool			getHot() const;

		// Movements
		bool	isOnGround(Grid &grid, const int y);
		bool	fallDown(Grid &grid, const int x, const int y);
		bool	fallLeft(Grid &grid, const int x, const int y);
		bool	fallRight(Grid &grid, const int x, const int y);
		bool	moveLeft(Grid &grid, const int x, const int y);
		bool	moveRight(Grid &grid, const int x, const int y);
		bool	riseUp(Grid &grid, const int x, const int y);
		bool	riseLeft(Grid &grid, const int x, const int y);
		bool	riseRight(Grid &grid, const int x, const int y);

	protected:
		unsigned int	_id = EMPTY_BLOCK;
		unsigned int	_type = EMPTY_TYPE;
		bool			_isElectrified = false;
		unsigned int	_isHot = false;

	private:
		// OpenGL
		static unsigned int	_VAO;	// Vertex Array Object
		static unsigned int	_VBO;	// Vertex Buffer Object
		static unsigned int	_EBO;	// Element Buffer Object
		static unsigned int	_instanceVBO;
		static unsigned int	_colorVBO;

		// Block
		bool		_isUpdated = false;
		glm::vec3	_blockColor;
};
