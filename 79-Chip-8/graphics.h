#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "chip8.h"

class Graphics
{
private:
	SDL_Window* window; 
	SDL_Renderer* renderer;
	int zoom;
public:
	Graphics(int _zoom);
	~Graphics();
	bool setup();
	void draw(Chip8 chip);
	void destroy();
};