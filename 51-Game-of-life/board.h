#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

class Board
{
public:
	Board(int _width, int _height, std::string rules, bool _torus);
	~Board();
	
	int count_neighbours(int x, int y);
	void step();

	int width, height;
	std::vector<int> board;
	int step_num;
	bool paused, torus;
	std::unordered_set<int> rules_live, rules_born;
};