#pragma once

# include "ABlock.hpp"
# include "WaterBlock.hpp"

class	SteamBlock : public ABlock
{
	public:
		SteamBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
