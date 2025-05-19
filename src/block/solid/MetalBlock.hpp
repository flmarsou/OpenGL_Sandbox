#pragma once

# include "ABlock.hpp"

class	MetalBlock : public ABlock
{
	public:
		MetalBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		glm::vec3	offColor();
		glm::vec3	onColor();

		glm::vec3	_defaultColor;

		bool	checkBatteries(const Grid &grid, const int x, const int y);
		void	floodFillOn(const Grid &grid, const int x, const int y);
};
