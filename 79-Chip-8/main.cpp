// TODO: fix blocking sound, fix terminal-like keyboard

#include <stdio.h>
#include "chip8.h"
#include "graphics.h"

unsigned short get_key(int keysym);

int main(int argc, char const *argv[])
{
	if(argc < 2)
	{
		std::cerr << "No filename specified!" << std::endl;
		return 1;
	}

	// ROM filename
	std::string filename(argv[1]);
	// Chip-8 singleton
	Chip8 chip(false);
	// If true, application should exit
	bool quit = false;
	// Graphics
	const int zoom = 8;
	Graphics graphics(zoom);

	// Initialize audio for those quality beeps
	SDL_Init(SDL_INIT_AUDIO);

	// Setup render system and input register input callbacks
	if(graphics.setup())
	{
		std::cerr << "Failed to setup graphics!" << std::endl;
		return 2;
	}

	// Initialize system and load the game into memory
	if(chip.load_game(filename))
	{
		std::cerr << "Could not open file: " << filename << std::endl;
		return 3;
	}

	// Main emulation loop
	while(!quit)
	{
		// Handle events on queue
		SDL_Event e;
		while(SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			if(e.type == SDL_KEYDOWN)
			{
				unsigned char key_num = get_key(e.key.keysym.sym);
				chip.press_key(key_num);
			}
			if(e.type == SDL_KEYUP)
			{
				unsigned char key_num = get_key(e.key.keysym.sym);
				chip.release_key(key_num);
			}
		}
		if(!chip.halt_flag && !chip.key_wait)
			chip.emulate_cycle();

		// If the draw flag is set, update the screen
		if(chip.draw_flag)
			graphics.draw(chip);

		// Delay to emulate CPU frequency
		SDL_Delay(1000 / 540);
		// SDL_Delay(0);
	}

	graphics.destroy();

	return 0;
}

// Parse SDL keysym (event.key.keysym.sym) to Chip-8 key
unsigned short get_key(int keysym)
{
	// 1 2 3 4  -  1 2 3 c
	// q w e r  -  4 5 6 d
	// a s d f  -  7 8 9 e
	// z x c v  -  a 0 b f
	switch(keysym)
	{	
		case SDLK_1: return 0x1;
		case SDLK_2: return 0x2;
		case SDLK_3: return 0x3;
		case SDLK_4: return 0xC;
		case SDLK_q: return 0x4;
		case SDLK_w: return 0x5;
		case SDLK_e: return 0x6;
		case SDLK_r: return 0xD;
		case SDLK_a: return 0x7;
		case SDLK_s: return 0x8;
		case SDLK_d: return 0x9;
		case SDLK_f: return 0xE;
		case SDLK_z: return 0xA;
		case SDLK_x: return 0x0;
		case SDLK_c: return 0xB;
		case SDLK_v: return 0xF;
	}
	return -1;
}