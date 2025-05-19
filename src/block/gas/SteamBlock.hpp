#pragma once

# include "AGas.hpp"

class	SteamBlock : public AGas
{
	public:
		SteamBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
