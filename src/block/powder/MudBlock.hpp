#pragma once

# include "APowder.hpp"

class	MudBlock : public APowder
{
	public:
		MudBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		bool	_stuck;
};
