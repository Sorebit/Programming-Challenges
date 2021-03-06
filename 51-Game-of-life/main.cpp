// Usage:
// ./life.app <rules_live> <rules_born>
// ex. ./life.app 23 3 => RULES: 23/3
// ex. ./life.app - 2  => RULES: /2
// ex. .life.app 123 - => RULES: 123/

#include <SDL2/SDL.h>
#include <iostream>
#include <regex>
#include <chrono>
		
#include "board.h"
#include "graphics.h"

std::string parse_rules(std::string a, std::string b);

int main(int argc, char *argv[])
{
	using mili_t = std::chrono::milliseconds;
	using tp_t = std::chrono::system_clock::time_point;

	tp_t now = std::chrono::system_clock::now();
	tp_t next_tick = std::chrono::system_clock::now();
	mili_t delay(100);

	const int Board_height = 32;
	const int Board_width = 32;
	const int Board_zoom = 15;

	bool interrupted = false;
	bool mouse_pressed[2] = { false, false };
	
	std::cout << "Cellular automaton" << std::endl;
	Graphics graphics(Board_width, Board_height, Board_zoom);
	graphics.setup();
	
	std::string rules;
	if(argc == 3)
		rules = parse_rules(std::string(argv[1]), std::string(argv[2]));
	else
	{
		std::cout << "Expected 2 arguments, falling back to rules 23/3" << std::endl;
		rules = "23/3";
	}

	// Create a finite (non-torus) board
	Board board(Board_width, Board_height, rules, false);

	// Main loop
	while(!interrupted)
	{
		// Process events
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				interrupted = true;
			}
			if(e.type == SDL_KEYDOWN)
			{
				int key = e.key.keysym.sym;
				if(key == SDLK_SPACE)
				{
					board.paused ^= 1;
				}
			}
			if(e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT) mouse_pressed[0] = true;
				if (e.button.button == SDL_BUTTON_RIGHT) mouse_pressed[1] = true;
			}
			if(e.type == SDL_MOUSEBUTTONUP)
			{
				if (e.button.button == SDL_BUTTON_LEFT) mouse_pressed[0] = false;
				if (e.button.button == SDL_BUTTON_RIGHT) mouse_pressed[1] = false;
			}
		}

		// Process mouse state
		SDL_GetMouseState(&graphics.mx, &graphics.my);
		if(SDL_GetWindowFlags(graphics.window) & SDL_WINDOW_MOUSE_FOCUS)
		{
			// std::cout << mx << " " << my << std::endl;
			int px = std::ceil((float)graphics.mx / graphics.zoom) - 1;
			int py = std::ceil((float)graphics.my / graphics.zoom) - 1;
			if(py >= 0 && px >= 0 && px < Board_width && py < Board_height)
			{
				if(mouse_pressed[0])
				{
					board.board[py * board.width + px] = 1;
				}
				if(mouse_pressed[1])
				{
					board.board[py * board.width + px] = 0;
				}
			}
		}

		now = std::chrono::system_clock::now();
        
        if(now >= next_tick && !board.paused)
        {
			board.step();
            next_tick = now + delay;
			graphics.set_window_title("Cellular automaton (" + rules + ") Tick: " + std::to_string(board.step_num));
        }

		graphics.draw(board);

		SDL_Delay(10);
	}

	return 0;
}

// I couldn't get ^[0-8]*/[0-8]*$ to work
std::string parse_rules(std::string a, std::string b)
{
	std::string rules = "";
	std::regex base_regex("^[0-8]*$");
	std::smatch base_match;

	if(a != "-")
	{	
		if(std::regex_search(a, base_match, base_regex))
		{
			rules += a;
		}
		else 
		{
			std::cerr << "Regex a failed, falling back to rules 23/3" << std::endl;
			rules = "23/3";
			return rules;
		}
	}

	rules += "/";

	if(b != "-")
	{	
		if(std::regex_search(b, base_match, base_regex))
		{
			rules += b;
		}
		else
		{
			std::cerr << "Regex b failed, falling back to rules 23/3" << std::endl;
			rules = "23/3";
		}
	}


	return rules;
}