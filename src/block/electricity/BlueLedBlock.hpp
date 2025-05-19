#pragma once

# include "ABlock.hpp"

class	BlueLedBlock : public ABlock
{
	public:
		BlueLedBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		glm::vec3	colorOn();
		glm::vec3	colorOff();

		glm::vec3	_defaultColor;

		bool	checkElec(const Grid &grid, const int x, const int y);
		void	floodFill(const Grid &grid, const int x, const int y);
};
