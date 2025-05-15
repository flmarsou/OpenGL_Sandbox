#pragma once

# include "ABlock.hpp"

class	MudBlock : public ABlock
{
	public:
		MudBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		bool	_stuck;
};
