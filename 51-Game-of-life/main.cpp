#include <SDL2/SDL.h>
#include <iostream>

#include "life.h"
#include "graphics.h"


int main(int argc, char *argv[])
{
	const int Board_height = 32;
	const int Board_width = 32;
	bool interrupted = false;
	
	std::cout << "Game of life" << std::endl;
	Graphics graphics(Board_width, Board_height, 15);
	graphics.setup();

	Life life(Board_width, Board_height, "23/3", true);

	life.board[Board_width + 4] = life.board[Board_width * 2 + 2] = 
	life.board[Board_width * 2 + 4] = life.board[Board_width * 3 + 3] = 
	life.board[Board_width * 3 + 4] = 1;
	life.board[Board_width * 6 + 3] = life.board[Board_width * 7 + 3] = life.board[Board_width * 8 + 3] = 1;

	while(!interrupted)
	{
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
			if(e.type == SDL_KEYUP)
			{
				// int key = e.key.keysym.sym;

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