#include "life.h"

Life::Life(int _width, int _height, std::string rules, bool _torus)
{
	width = _width;
	height = _height;
	torus = _torus;

	board.resize(width * height, 0);
	step_num = 0;
	paused = true;

	std::cout << "RULES: " << rules << std::endl;
	bool delimiter_reached = false;
	for(auto i : rules)
	{
		if(i == '/')
		{
			delimiter_reached = true;
			continue;
		}
		int n = static_cast<int>(i - '0');
		if(n < 0 || n > 8)
			continue;
		if(!delimiter_reached)
			rules_live.insert(n);
		else
			rules_born.insert(n);
	}
}

Life::~Life()
{

}

int Life::count_neighbours(int x, int y)
{
	int res = 0;
	for(int i = -1; i <= 1; ++i)
	{
		int yi = y + i;
		if(torus)
		{		
			if(yi < 0)
				yi += height;
			else if(yi >= height)
				yi -= height;
		}
		else
		{
			if(yi < 0 || yi >= height)
				continue;
		}

		for(int j = -1; j <= 1; ++j)
		{
			int xj = x + j;
			if(torus)
			{
				if(xj < 0)
					xj += width;
				if(xj >= width)
					xj -= width;
			}
			else
			{	
				if(xj < 0 || xj >= width)
					continue;
			}
			if(i == 0 && j == 0)
				continue;
			if(board[yi * width + xj])
				++res;
		}
	}
	return res;
}

void Life::step()
{
	std::vector<int> tmp;
	tmp.resize(board.size());

	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			int n = count_neighbours(x, y);
			int pos = y * width + x;
			if(board[pos] && rules_live.count(n))
			{
				tmp[pos] = 1;
			}
			if(!board[pos] && rules_born.count(n))
			{
				tmp[pos] = 1;
			}
		}
	}

	board = tmp;

	++step_num;
}