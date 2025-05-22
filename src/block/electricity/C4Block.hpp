#pragma once

# include "AElectricity.hpp"

class	C4Block : public AElectricity
{
	public:
		C4Block();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		void	floodFill(const Grid &grid, const int x, const int y) const;
		bool	_detonate;
};
