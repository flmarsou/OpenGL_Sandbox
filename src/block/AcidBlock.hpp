#pragma once

# include "ABlock.hpp"

enum	acidSeverity
{
	NONE,
	WEAK,
	STRONG
};

class	AcidBlock : public ABlock
{
	public:
		AcidBlock();

		void	update(Grid &grid, const int x, const int y) override;

		private:
			void	randomizeColor();
			bool	checkSurrounding(const Grid &grid, const int &x, const int &y);
			void	setSeverity(const Grid &grid, const int &x, const int &y);

			unsigned int	_bottom = NONE;
			unsigned int	_bottomLeft = NONE;
			unsigned int	_bottomRight = NONE;
			unsigned int	_left = NONE;
			unsigned int	_right = NONE;
			unsigned int	_top = NONE;
			unsigned int	_topLeft = NONE;
			unsigned int	_topRight = NONE;
};
