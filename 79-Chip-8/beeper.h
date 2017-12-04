#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <queue>
#include <cmath>

struct BeepObject
{
	double freq;
	int samplesLeft;
};


class Beeper
{
private:
	const int AMPLITUDE = 28000;
	const int FREQUENCY = 44100;
	double v;
	std::queue<BeepObject> beeps;
public:
	Beeper();
	~Beeper();
	void beep(double freq, int duration);
	void generateSamples(Sint16 *stream, int length);
	void wait();
};
