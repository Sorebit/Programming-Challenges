#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "life.h"

class Graphics
{
private:
public:
	SDL_Window *window; 
	SDL_Renderer *renderer;
	int zoom;
	int width, height;
	int mx, my;
	Graphics(int _width, int _height, int _zoom);
	~Graphics();
	bool setup();
	void draw(Life life);
};