// TODO: Synthesize sound instead of playing it from a *.wav file

#include <cstdio>
#include <unordered_map>
#include "chip8.h"
#include "graphics.h"
#include "audio.h"

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

	// Setup render system and input register input callbacks
	if(graphics.setup())
	{
		std::cerr << "Failed to setup graphics!" << std::endl;
		quit = true;
	}

	// Audio
	Audio audio;
	if(audio.setup())
	{
		std::cerr << "Failed to setup audio!" << std::endl;
		quit = true;
	}

	// Initialize system and load the game into memory
	if(chip.load_game(filename))
	{
		std::cerr << "Could not open file: " << filename << std::endl;
		quit = true;
	}

	// Map SDL keysym (event.key.keysym.sym) to Chip-8 keys
	// 1 2 3 4  -  1 2 3 c
	// q w e r  -  4 5 6 d
	// a s d f  -  7 8 9 e
	// z x c v  -  a 0 b f
	std::unordered_map<int, int> key_map 
	{
		{SDLK_1, 0x1}, {SDLK_2, 0x2}, {SDLK_3, 0x3}, {SDLK_4, 0xC},
		{SDLK_q, 0x4}, {SDLK_w, 0x5}, {SDLK_e, 0x6}, {SDLK_r, 0xD},
		{SDLK_a, 0x7}, {SDLK_s, 0x8}, {SDLK_d, 0x9}, {SDLK_f, 0xE},
		{SDLK_z, 0xA}, {SDLK_x, 0x0}, {SDLK_c, 0xB}, {SDLK_v, 0xF},
	};

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
				unsigned char key_num = key_map[e.key.keysym.sym];
				chip.press_key(key_num);
			}
			if(e.type == SDL_KEYUP)
			{
				unsigned char key_num = key_map[e.key.keysym.sym];
				chip.release_key(key_num);
			}
		}
		if(!chip.halt_flag && !chip.key_wait)
		{
			chip.emulate_cycle();
		}
		
		if(chip.beep_flag)
		{
			audio.beep();
			chip.beep_flag = false;
		}

		// If the draw flag is set, update the screen
		if(chip.draw_flag)
			graphics.draw(chip);

		// Delay to emulate CPU frequency
		SDL_Delay(1000 / 540);
		// SDL_Delay(0);
	}

	return 0;
}