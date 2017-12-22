#include "graphics.h"

Graphics::Graphics(int _width, int _height, int _zoom)
{
	window = NULL;
	renderer = NULL;
	zoom = _zoom;
	width = _width;
	height = _height;
}

Graphics::~Graphics()
{
	// Destroy window and quit
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_Quit();
}

bool Graphics::setup()
{
	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return true;
	}

	// Create window
	window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width*zoom, height*zoom, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return true;
	}

	// Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
	{
		std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return true;
	}
	
	if(SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0)
	{
		std::cerr << "SDL could set blend mode! SDL Error: " << SDL_GetError() << std::endl;
		return true;
	}

	return false;

}

void Graphics::draw(Life life)
{
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	// Set accent color
	SDL_SetRenderDrawColor(renderer, 0xEE, 0xEE, 0xEE, 0xFF);

	// Draw cells
	for(unsigned i = 0; i < life.board.size(); ++i)
	{
		int x = i % life.width;
		int y = i / life.width;
		if(!life.board[i])
		{
			SDL_SetRenderDrawColor(renderer, 0x30, 0x30, 0x30, 0xFF);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0xEE, 0xEE, 0xEE, 0xFF);	
		}

		SDL_Rect fillRect = { x*zoom + 1, y*zoom + 1, zoom - 2, zoom - 2};
		SDL_RenderFillRect(renderer, &fillRect);
	}

	if(life.paused)
	{		
		// Draw pause symbol
		int h = (std::min(width, height) * zoom) / 8;
		int w = h / 3;
		int x = (width * zoom ) / 2 - (w * 3) / 2;
		int y = (height * zoom - h) / 2;
		int p = 2; // padding
		SDL_Rect fillRect;

		// Draw overlay; 
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x40);
		fillRect = { 0, 0, width * zoom, height * zoom };
		SDL_RenderFillRect(renderer, &fillRect);

		SDL_SetRenderDrawColor(renderer, 0x60, 0x60, 0x60, 0xFF);
		fillRect = { x - p, y - p, w + 2*p, h + 2*p};
		SDL_RenderFillRect(renderer, &fillRect);
		fillRect = { x + w * 2 - p, y - p, w + 2*p, h + 2*p};
		SDL_RenderFillRect(renderer, &fillRect);

		SDL_SetRenderDrawColor(renderer, 0xE0, 0xE0, 0xE0, 0xFF);
		fillRect = { x, y, w, h };
		SDL_RenderFillRect(renderer, &fillRect);
		fillRect = { x + w * 2, y, w, h };
		SDL_RenderFillRect(renderer, &fillRect);
	}

	// Update screen
	SDL_RenderPresent(renderer);
}
