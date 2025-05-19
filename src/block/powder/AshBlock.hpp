#pragma once

# include "APowder.hpp"

class	AshBlock : public APowder
{
	public:
		AshBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
