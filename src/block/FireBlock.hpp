#pragma once

# include "ABlock.hpp"

class	FireBlock : public ABlock
{
	public:
		FireBlock(unsigned int extinguishRate);

		void	update(Grid &grid, const int x, const int y) override;

	private:
		void	randomizeYellow();
		void	randomizeDarkYellow();
		void	randomizeOrange();
		void	randomizeDarkOrange();
		void	randomizeRed();

		bool	extinguishRate();

		int	_extinguishRate;
		int	_extinguishColor;
};
