#pragma once

# include "ABlock.hpp"

class	SteamBlock : public ABlock
{
	public:
		SteamBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
