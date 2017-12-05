#include "graphics.h"

Graphics::Graphics(int _zoom)
{
	window = NULL;
	renderer = NULL;
	zoom = _zoom;
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
	window = SDL_CreateWindow("Chip-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 64*zoom, 32*zoom, SDL_WINDOW_SHOWN);
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

void Graphics::draw(Chip8 chip)
{
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	// Set accent color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Draw pixels
	for(int i = 0; i < 64*32; ++i)
	{
		int x = i % 64;
		int y = i / 64;
		if(chip.gfx[i])
		{		
			SDL_Rect fillRect = { x*zoom, y*zoom, zoom, zoom };
			SDL_RenderFillRect(renderer, &fillRect);
		}
	}

	// Update screen
	SDL_RenderPresent(renderer);
}
