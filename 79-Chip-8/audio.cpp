#include "audio.h"

Audio::Audio()
{
	beep_file = NULL;
}

Audio::~Audio()
{
	//Free sounds
	Mix_FreeChunk(beep_file);
	beep_file = NULL;

	// Quit SDL Mixer
	Mix_Quit();
}

bool Audio::setup()
{
	// Initialize audio for those quality beeps
	SDL_Init(SDL_INIT_AUDIO);

	 //Initialize SDL_mixer
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return 1;
	}

	// Open beep file
	beep_file = Mix_LoadWAV("Assets/beep.wav");
	if(beep_file == NULL)
	{
		std::cerr << "Failed to load beep sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return 1;
	}

	return 0;
}

void Audio::beep()
{
	Mix_PlayChannel(-1, beep_file, 0);
}