#pragma once

# include "APowder.hpp"

class	DynamiteBlock : public APowder
{
	public:
		DynamiteBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
