#include <SDL2/SDL.h>
#include <iostream>

#include "life.h"
#include "graphics.h"

int main(int argc, char *argv[])
{
	std::cout << "Game of life" << std::endl;
	Graphics graphics(50, 50, 15);
	graphics.setup();

	bool interrupted = false;

	Life life(50, 50, "23/3");

	life.board[54] = life.board[102] = life.board[104] = life.board[153] = life.board[154] = 1;
	life.board[303] = life.board[353] = life.board[403] = 1;

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
				// int key = e.key.keysym.sym;

			}
			if(e.type == SDL_KEYUP)
			{
				// int key = e.key.keysym.sym;

			}
		}

		graphics.draw(life);
		life.step();
		SDL_Delay(1000 / 10);

	}

	return 0;
}

// . . . .
// . . . #
// . # . #
// . . # #