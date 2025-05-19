#pragma once

# include "APowder.hpp"

class	SandBlock : public APowder
{
	public:
		SandBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
