#pragma once

# include "ABlock.hpp"
# include "SandBlock.hpp"
# include "SteamBlock.hpp"

class	WaterBlock : public ABlock
{
	public:
		WaterBlock();

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		bool	convertSurrounding(Grid &grid, const int x, const int y);
};
