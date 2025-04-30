#pragma once

# include "ABlock.hpp"

class	SandBlock : public ABlock
{
	public:
		SandBlock();

		void	draw(float x, float y, float scale, unsigned int &shader) const override;
		void	update(Grid &grid, unsigned int x, unsigned int y) override;

	private:
		glm::vec3	_blockColor;
};
