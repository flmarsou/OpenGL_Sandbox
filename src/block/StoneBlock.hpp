#pragma once

# include "ABlock.hpp"

class	StoneBlock : public ABlock
{
	public:
		StoneBlock();

		void	draw(float x, float y, float scale, unsigned int &shader) const override;
		void	update(Grid &grid, int x, int y) override;

	private:
		glm::vec3	_blockColor;

		void	randomizeColor();
};
