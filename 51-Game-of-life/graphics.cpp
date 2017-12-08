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
	window = SDL_CreateWindow("Chip-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width*zoom, height*zoom, SDL_WINDOW_SHOWN);
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
		
	return false;

}

void Graphics::draw(Life life)
{
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	// Set accent color
	SDL_SetRenderDrawColor(renderer, 0xEE, 0xEE, 0xEE, 0xFF);

	// Draw pixels
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

	// Update screen
	SDL_RenderPresent(renderer);
}
