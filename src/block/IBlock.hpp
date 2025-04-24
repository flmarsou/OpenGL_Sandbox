#pragma once

class	Grid;

class	IBlock
{
	public:
		virtual void	drawBlock(unsigned int x, unsigned int y) const = 0;
		virtual	~IBlock() {}
};
