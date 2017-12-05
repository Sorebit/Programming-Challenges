#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

class Chip8
{
public:
	void initialize(bool _shift_x);
	void emulate_cycle();
	void press_key(unsigned short key_num);
	void release_key(unsigned short key_num);
	void halt();
	bool load_game(std::string);

	// Opcode
	unsigned short opcode;

	// 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
	// 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
	// 0x200-0xFFF - Program ROM and work RAM
	unsigned char memory[4096]; // 0x1000

	// Registers
	unsigned char V[16];

	// Index register and program counter
	unsigned short I;
	unsigned short pc;
	// If 1, emulate_cycle doesn't move pc at the end of a cycle (used for jumps)
	bool skip_pc_add_flag;

	// The graphics system: 
	// The chip 8 has one instruction that draws sprite to the screen. 
	// Drawing is done in XOR mode and if a pixel is turned off as a 
	// result of drawing, the VF register is set. 
	// This is used for collision detection.
	// The graphics of the Chip 8 are black and white and 
	// the screen has a total of 2048 pixels (64 x 32). 
	// This can easily be implemented using an array that hold the pixel state (1 or 0):
	unsigned char gfx[64 * 32];
	// If 1 screen is drawn, then set to 0 again
	bool draw_flag;

	// Timer registers that count at 60Hz
	// Whenever sound timer reaches 0 system buzzer sounds
	unsigned char delay_timer; 
	unsigned char sound_timer; 

	// The stack is used to remember the current location 
	// before a jump is performed. So anytime system performs
	// a jump or call a subroutine, it should store the program
	// counter in the stack before proceeding. 
	// The system has 16 levels of stack.
	unsigned short stack[16];
	unsigned short sp;

	// State of hex keyoad
	unsigned char key[16];
	// Register to which we should write as callback
	unsigned short key_wait;

	// If set to 1 - emulator stops
	bool halt_flag;
	bool beep_flag;

	// Options
	// If set to 1 opcodes 0x8XY6 and 0x8XYE shift VX rather than shifting VY and copying it to VX
	bool shift_x;

	// Predefined fontset to be loaded at the beginning of memory
	unsigned char fontset[80] = 
	{ 
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F 
	};	

	Chip8(bool _shift_x);
	~Chip8();
};
