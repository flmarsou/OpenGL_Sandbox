#pragma once

# include "ABlock.hpp"

class	MetalBlock : public ABlock
{
	public:
		MetalBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		glm::vec3	_defaultColor;

		const glm::vec3	colorOff() const;
		const glm::vec3	colorOn() const;

		void	floodFill(const Grid &grid, const int x, const int y) const;
};
