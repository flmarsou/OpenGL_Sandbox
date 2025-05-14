#pragma once

# include "ABlock.hpp"

class	MudBlock : public ABlock
{
	public:
		MudBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		bool	_stuck;
};
