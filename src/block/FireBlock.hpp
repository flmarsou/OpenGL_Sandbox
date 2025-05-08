#pragma once

# include "ABlock.hpp"

class	FireBlock : public ABlock
{
	public:
		FireBlock(unsigned int extinguishRate);

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeColor();

		unsigned int	_extinguishRate;
};
