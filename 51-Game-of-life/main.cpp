// TODO:
// [ ] Separate SDL clock and board clock (ie. it runs at ex. 60fps and still does 10 ticks per sec)

// Usage:
// ./life.app <rules_live> <rules_born>
// ex. ./life.app 23 3 => RULES: 23/3
// ex. ./life.app - 2  => RULES: /2
// ex. .life.app 123 - => RULES: 123/

#include <SDL2/SDL.h>
#include <iostream>
#include <regex>

#include "life.h"
#include "graphics.h"

std::string parse_rules(std::string a, std::string b);

int main(int argc, char *argv[])
{
	const int Board_height = 32;
	const int Board_width = 32;
	const int Board_zoom = 15;

	bool interrupted = false;
	bool mouse_pressed[2] = { false, false };
	
	std::cout << "Game of life" << std::endl;
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
	Life life(Board_width, Board_height, rules, false);

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
					life.paused ^= 1;
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
					life.board[py * life.width + px] = 1;
				}
				if(mouse_pressed[1])
				{
					life.board[py * life.width + px] = 0;
				}
			}
		}

		graphics.draw(life);

		if(!life.paused)
		{
			life.step();
		}

		SDL_Delay(1000 / 10);
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