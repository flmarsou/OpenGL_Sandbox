#pragma once

# include "AGas.hpp"

class	FlammableGasBlock : public AGas
{
	public:
		FlammableGasBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		bool	_burning;
		bool	checkFire(Grid &grid, const int x, const int y) const;
};
