#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

class Life
{
public:
	Life(int _width, int _height, std::string rules);
	~Life();
	
	int count_neighbours(int x, int y);
	void step();

	int width, height;
	std::vector<int> board;
	int step_num;
	std::unordered_set<int> rules_live, rules_born;
};