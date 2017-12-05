#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Audio
{
private:
	Mix_Chunk *beep_file;
public:
	Audio();
	~Audio();
	bool setup();
	void beep();
};
