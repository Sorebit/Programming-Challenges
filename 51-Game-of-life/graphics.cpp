#include "graphics.h"

Graphics::Graphics(int _width, int _height, int _zoom)
{
	window = NULL;
	renderer = NULL;
	zoom = _zoom;
	width = _width;
	height = _height;
	mx = -1;
	my = -1;
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
	window = SDL_CreateWindow("Cellular automaton (-/-) Tick: 0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
							  width*zoom, height*zoom, SDL_WINDOW_SHOWN);
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

void Graphics::draw(Board board)
{

	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	// Set accent color
	SDL_SetRenderDrawColor(renderer, 0xEE, 0xEE, 0xEE, 0xFF);

	// Draw cells
	for(unsigned i = 0; i < board.board.size(); ++i)
	{
		int x = i % board.width;
		int y = i / board.width;
		if(!board.board[i])
		{
			SDL_SetRenderDrawColor(renderer, 0x30, 0x30, 0x30, 0xFF);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0xDD, 0xDD, 0xDD, 0xFF);	
		}

		SDL_Rect fillRect = { x*zoom + 1, y*zoom + 1, zoom - 2, zoom - 2};
		SDL_RenderFillRect(renderer, &fillRect);
	}

	if(board.paused)
	{		
		// Draw overlay; 
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x17);
		SDL_Rect fillRect = { 0, 0, width * zoom, height * zoom };
		SDL_RenderFillRect(renderer, &fillRect);
	}

	// Draw mouse
	{
		int px = std::ceil((float)mx / zoom) - 1;
		int py = std::ceil((float)my / zoom) - 1;
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x90);
		SDL_Rect fillRect = { px * zoom, py * zoom, zoom, zoom };
		SDL_RenderFillRect(renderer, &fillRect);
	}

	// Update screen
	SDL_RenderPresent(renderer);
}

void Graphics::set_window_title(std::string title)
{
	SDL_SetWindowTitle(window, title.c_str());
}