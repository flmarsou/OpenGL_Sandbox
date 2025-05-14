#pragma once

# include "debug.hpp"
# include "Grid.hpp"

# include <GLAD/glad.h>

# include <GLM/glm.hpp>
# include <GLM/gtc/matrix_transform.hpp>
# include <GLM/gtc/type_ptr.hpp>

enum	blockID
{
	EMPTY_BLOCK,
	SAND_BLOCK,
	WATER_BLOCK,
	STONE_BLOCK,
	BOMB_BLOCK,
	FIRE_BLOCK,
	ACID_BLOCK,
	WOOD_BLOCK,
	ASH_BLOCK,
	TOXIC_SLUDGE_BLOCK,
	FLAMMABLE_GAS_BLOCK,
	STEAM_BLOCK,
	MUD_BLOCK
};

enum	blockType
{
	EMPTY_TYPE,
	POWDER_TYPE
};

class	Grid;

class	ABlock
{
	public:
		virtual ~ABlock() {}

		static void	initBlock();
		static void	deleteBlock();

		void			draw(const float x, const float y, const float scale, const unsigned int shader) const;
		virtual void	update(Grid &grid, const int x, const int y) = 0;

		void			setUpdate(const bool isUpdated);
		bool			getUpdate() const;
		void			setColor(const glm::vec3 color);
		void			setId(const unsigned int id);
		unsigned int	getId() const;
		void			setType(const unsigned int type);
		unsigned int	getType() const;

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

	private:
		// OpenGL
		static unsigned int	_VAO;	// Vertex Array Object
		static unsigned int	_VBO;	// Vertex Buffer Object
		static unsigned int	_EBO;	// Element Buffer Object

		// Block
		bool		_isUpdated = false;
		glm::vec3	_blockColor;
};
