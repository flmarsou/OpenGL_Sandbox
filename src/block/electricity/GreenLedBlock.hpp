#pragma once

# include "AElectricity.hpp"

class	GreenLedBlock : public AElectricity
{
	public:
		GreenLedBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		glm::vec3	colorOn();
		glm::vec3	colorOff();

		glm::vec3	_defaultColor;

		void	floodFill(const Grid &grid, const int x, const int y);
};
