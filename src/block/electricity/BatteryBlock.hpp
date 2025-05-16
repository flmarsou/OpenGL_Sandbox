#pragma once

# include "ABlock.hpp"

class	BatteryBlock : public ABlock
{
	public:
		BatteryBlock();

		ABlock	*clone() const override;
		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();
};
