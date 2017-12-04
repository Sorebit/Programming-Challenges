// Text to morse code
// Written as part of /g/'s programming challenge
//
// uses aplay to playback sounds
//
// Reference: https://en.wikipedia.org/wiki/Morse_code
// Doesn't support characters not recommended by ITU-R
//
// short mark, dot or "dit" (·) : "dot duration" is one time unit long
// longer mark, dash or "dah" (–) : three time units long
// inter-element gap between the dots and dashes within a character : one dot duration or one unit long
// short gap (between letters) : three time units long
// medium gap (between words) : seven time units long
// (https://en.wikipedia.org/wiki/Morse_code#Representation.2C_timing_and_speeds)
//
// Time unit used here is 50 ms making the transmission 12 wpm (words per minute)
// as "Paris" takes exactly (50 * time unit) ms
//
// Uses two .wav files from sounds folder (I'm probably not going to add command line arguments)
// sounds/
// -  dot.wav        : 50 ms of 440 Hz sine wave
// -  dash.wav       : 150 ms of 440 Hz sine wave
// -  short_gap.wav  : 150 ms of silence
// -  medium_gap.wav : 350 ms of silence
// 
// Sorebit - https://github.com/Sorebit/

#include <stdio.h>
#include <stdlib.h>

#define UNDEF_CHAR 0
#define LETTER 1
#define NUM 27
#define SPACE 37
#define PERIO 38
#define COMMA 39
#define QUEST 40
#define APOST 41
#define EXCLA 42
#define SLASH 43
#define PAROP 44
#define PARCL 45
#define COLON 46
#define SEMIC 47
#define DDASH 48
#define PLUSS 49
#define HYPHE 50
#define QUOTA 51
#define ATSIG 52 

char* ck[] = {
	// undefined character
	"#",
	// a-z
	".-", "-...", "-.-.", "-..", ".", "..-.","--.",
	"....", "..", ".---", "-.-", ".-..", "--", "-.", 
	"---", ".--.", "--.-", ".-.", "...", "-", 
	"..-", "...-", ".--", "-..-", "-.--", "--..",
	// Numerals
	"-----", ".----", "..---", "...--", "....-",
	".....", "-....", "--...", "---..", "----.",
	// Space [ ]
	"/",
	// Period [.]
	".-.-.-",
	// Comma [,]
	"--..--",
	// Question mark [?]
	"..--..",
	// Apostrophe [']
	".----.",
	// Exclamation Point [!]
	"-.-.--",
	// SlashFraction Bar [/]
	"-..-.",
	// Parenthesis (Open)
	"-.--.",
	// Parenthesis (Close)
	"-.--.-",
	// Colon [:]
	"---...",
	// Semicolon [;]
	"-.-.-.",
	// Double Dash [=]
	"-...-",
	// Plus sign [+]
	".-.-.",
	// Hyphen, Minus Sign [-]
	"-....-",
	// Quotation mark ["]
	".-..-.",
	// At Sign [@]
	".--.-.",
};

int char_to_index(char c)
{
	// Lowercase
	if(c >= 'a' && c <= 'z') return c - 'a' + LETTER;
	// Uppercase
	if(c >= 'A' && c <= 'Z') return c - 'A' + LETTER;
	// Numbers
	if(c >= '0' && c <= '9') return c - '0' + NUM;
	// Special character
	if(c == ' ')  return SPACE;
	if(c == '.')  return PERIO;
	if(c == ',')  return COMMA;
	if(c == '?')  return QUEST;
	if(c == '\'') return APOST;
	if(c == '!')  return EXCLA;
	if(c == '/')  return SLASH;
	if(c == '(')  return PAROP;
	if(c == ')')  return PARCL;
	if(c == ':')  return COLON;
	if(c == ';')  return SEMIC;
	if(c == '=')  return DDASH;
	if(c == '+')  return PLUSS;
	if(c == '-')  return HYPHE;
	if(c == '"')  return QUOTA;
	if(c == '@')  return ATSIG;

	// Undefined character
	return UNDEF_CHAR;
}

int main(int argc, char const *argv[])
{
	// Input char
	char c;
	// Letter buffer
	char* buff;
	// Buffer indexing
	int i;

	printf("Text to morse code converter - Sorbet.\n");
	printf("Written as part of /g/'s programming chalenges.\n");
	printf("Input text to convert:\n");

	while((c = getchar()) != '\n' && c != EOF)
	{
		buff = ck[char_to_index(c)];
		i = 0;
		if(buff[i] == '/')
		{
			// Between words
			system("aplay sounds/medium_gap.wav &> /dev/null");
			putchar('/');
			continue;
		}
		// Normal character
		while(buff[i++] != '\0')
		{
			if(buff[i - 1] == '.') {
				system("aplay sounds/dot.wav &> /dev/null");
				putchar('.');
			}
			else {
				system("aplay sounds/dash.wav &> /dev/null");
				putchar('-');
			}
		}
		// Between letters
		system("aplay sounds/short_gap.wav &> /dev/null");
		putchar(' ');
	}

	printf("\n");
	return 0;
}