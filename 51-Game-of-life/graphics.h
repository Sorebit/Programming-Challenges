#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "life.h"

class Graphics
{
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
	void set_window_title(std::string title);
};