#include "chip8.h"

// #define DEBUG
// #define STATE

Chip8::Chip8(bool _shift_x) { initialize(_shift_x); }
Chip8::~Chip8() {}

void Chip8::initialize(bool _shift_x)
{
	// Options
	shift_x = _shift_x;

	// Program counter starts at 0x200
	pc = 0x200;
	opcode = 0;
	I = 0;

	// Clear display
	for(int i = 0; i < 64 * 32; ++i) gfx[i] = 0;
	// Clear stack
	sp = 0;
	for(int i = 0; i < 0x10; ++i) stack[i] = 0;
	// Clear regsters V0-VF
	for(int i = 0; i < 0x10; ++i) V[i] = key[i] = 0;
	// Clear memory
	for(int i = 0; i < 0x1000; ++i) memory[i] = 0;

	// Load fontset
	for(int i = 0; i < 80; ++i) memory[i] = fontset[i];

	// Reset timers
	delay_timer = 0;
	sound_timer = 0;

	srand(time(NULL));
}

void Chip8::emulate_cycle()
{
	static Beeper b;
	// Fetch opcode
	opcode = memory[pc] << 8 | memory[pc + 1];
	short unsigned x   = (opcode & 0x0F00) >> 8;
	short unsigned y   = (opcode & 0x00F0) >> 4;
	short unsigned nn  = (opcode & 0x00FF) >> 0;
	short unsigned nnn = (opcode & 0x0FFF) >> 0;
	draw_flag = false;
	skip_pc_add_flag = false;
	key_wait = 0;

#ifdef DEBUG
	printf("[L %d][pc: 0x%x] >> 0x%4.4x | I: 0x%x | dt: 0x%x | st: 0x%x\n",
		(pc - 0x200) / 2 + 1, pc, opcode, I, delay_timer, sound_timer);
#endif

	// Decode opcode
	switch(opcode & 0xF000)
	{
		case 0x0000:
			// Not sure about 0x0NNN
			switch(opcode & 0x00FF)
			{
				case 0xE0: // 0x00E0: Clears the screen
					for(int i = 0; i < 64 * 32; i++)
						gfx[i] = 0;
					draw_flag = true;
				break;
				case 0xEE: // 0x00E: Returns from subroutine
					pc = stack[sp - 1];
					--sp;
				break;
				default:
					halt();
					printf("Unknown opcode [0x0000]: 0x%x (pc: 0x%x)\n", opcode, pc);
			}
		break;
		case 0x1000: // 0x1NNN: Jumps to address NNN.
			pc = nnn;
			skip_pc_add_flag = true;
		break;
		case 0x2000: // 0x2NNN: Calls subroutine at NNN.
			stack[sp] = pc;
			++sp;
			pc = nnn;
			skip_pc_add_flag = true;
		break;
		case 0x3000: // 0x3XNN: Skips the next instruction if VX equals NN
			if(V[x] == nn) pc += 2;
		break;
		case 0x4000: // 0x4XNN: Skips the next instruction if VX doesn't equal NN
			if(V[x] != nn) pc += 2;
		break;
		case 0x5000: // 0x5XY0: Skips the next instruction if VX equals VY
			if(V[x] == V[y]) pc += 2;
		break;
		case 0x6000: // 0x6XNN: Sets VX to NN. 
			V[x] = nn;
		break;
		case 0x7000: // 0x7XNN: Adds NN to VX. (Carry flag is not changed)
			V[x] += nn;
		break;
		case 0x8000:
			switch(opcode & 0x000F)
			{
				case 0x0000: // 0x8XY0: Sets VX to the value of VY.
					V[x] = V[y];
				break;
				case 0x0001: // 0x8XY1: Sets VX to VX or VY. (Bitwise OR operation)
					V[x] |= V[y];
				break;
				case 0x0002: // 0x8XY2: Sets VX to VX and VY. (Bitwise AND operation)
					V[x] &= V[y];
				break;
				case 0x0003: // 0x8XY3: Sets VX to VX xor VY.
					V[x] ^= V[y];
				break;
				case 0x0004: // 0x8XY4: Adds VY to VX. VF is set to 1 when there's 
							 // a carry, and to 0 when there isn't.
					V[0xF] = (V[y] > (0xFF - V[x]));
					V[x] += V[y];
				break;
				case 0x0005: // 0x8XY5: VY is subtracted from VX.
							 // VF is set to 0 when there's a borrow, and 1 when there isn't.
					if(V[y] > V[x]) 
						V[0xF] = 0; // there is a borrow
					else 
						V[0xF] = 1;
					V[x] -= V[y];
				break;
				case 0x0006: // 0x8XY6: Shifts VY right by one and copies the result to VX. VF is  
							 // set to the value of the least significant bit of VY before the shift.
					if(shift_x)
					{
						V[0xF] = V[x] & 0x1;
						V[x] >>= 1;						
					}
					else
					{					
						V[0xF] = V[y] & 0x01;
						V[y] >>= 1;
						V[x] = V[y];
					}
				break;
				case 0x0007: // 0x8XY7: Sets VX to VY minus VX. VF is set to 0 when there's
							// a borrow, and 1 when there isn't.
					V[0xF] = (V[x] <= V[y]);
					V[x] = V[y] - V[x];
				break;
				case 0x000E: // 0x8XYE: Shifts VY left by one and copies the result to VX. VF is set
							 // to the value of the most significant bit of VY before the shift.
					if(shift_x)
					{					
						V[0xF] = V[x] & 0x80;
						V[x] <<= 1;
					}
					else
					{					
						V[0xF] = V[y] & 0x80;
						V[y] <<= 1;
						V[x] = V[y];
					}
				break;
				default:
					halt();
					printf("Unknown opcode [0x8000]: 0x%x\n", opcode);
			}
		break;
		case 0x9000: // 0x9XY0: Skips the next instruction if VX doesn't equal VY.
			if(V[x] != V[y]) pc += 2;
		break;
		case 0xA000: // ANNN: Sets I to the address NNN.
			I = nnn;
		break;
		case 0xB000: // 0xBNNN: Jumps to the address NNN plus V0.
			pc = nnn + V[0];
			skip_pc_add_flag = true;
		break;
		case 0xC000: // 0xCXNN: Sets VX to the result of a bitwise and operation on a random number 
					 // (0 to 255) and NN.
			V[x] = (rand() % 0xFF) & nn;
		break;
		case 0xD000:
		{
			// DXYN: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and
			// a height of N pixels. Each row of 8 pixels is read as bit-coded starting 
			// from memory location I; I value doesn’t change after the execution of this 
			// instruction. As described above, VF is set to 1 if any screen pixels are 
			// flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen.

			unsigned short x = V[(opcode & 0x0F00) >> 8];
			unsigned short y = V[(opcode & 0x00F0) >> 4];
			unsigned short height = opcode & 0x000F;
			unsigned short pixel, ppos;
			V[0xF] = 0;
			for(unsigned short yline = 0; yline < height; ++yline)
			{
				pixel = memory[I + yline];
				for(unsigned short xline = 0; xline < 8; ++xline)
				{
					if((pixel & (0x80 >> xline)) != 0)
					{
						ppos = (y + yline) * 64 + x + xline;
						if(y + yline < 32 && x + xline < 64)
						{						
							if(gfx[ppos] == 1)
								V[0xF] = 1;
							gfx[ppos] ^= 1;
						}

					}
				}
			}
			draw_flag = true;
		}
		break;
		case 0xE000:
			switch(opcode & 0x00FF)
			{
				case 0x009E: // 0xEX9E: Skips the next instruction if the key stored in VX is pressed.
					if(key[V[x]]) pc += 2;
				break;
				case 0x00A1: // 0xEXA1: Skips the next instruction if the key stored in VX isn't pressed.
					if(!key[V[x]]) pc += 2;
				break;
				default:
					halt();
					printf("Unknown opcode [0xE000]: 0x%x\n", opcode);
			}
		break;
		case 0xF000:
			switch(opcode & 0x00FF)
			{
				
				case 0x0007: // FX07: Sets VX to the value of the delay timer.
					V[x] = delay_timer;
				break;
				case 0x000A: // FX0A: A key press is awaited, and then stored in VX. 
							 // (Blocking Operation. All instruction halted until next key event)
					key_wait = x + 1;
#ifdef DEBUG
					printf("[ REQUEST KEY PRESS ] >> op: 0x%x\n", opcode);
#endif
				break;
				case 0x0015: // FX15: Sets the delay timer to VX.
					delay_timer = V[x];
				break;
				case 0x0018: // FX18: Sets the sound timer to VX.
					sound_timer = V[x];
				break;
				case 0x001E: // FX1E: Adds VX to I.
					// If I overflows 0x0FFF VF is set to 1, otherwise to 0
					V[0xF] = (I  > 0x0FFF - V[x]);
					I += V[x];
				break;
				case 0x0029: // FX29: Sets I to the location of the sprite for the character in VX.
							 // Characters 0-F (in hexadecimal) are represented by a 4x5 font.
					I = V[x] * 5;
				break;
				case 0x0033: // FX33: Stores the binary-coded decimal representation of VX, 
							 // with the most significant of three digits at the address in I,
							 // the middle digit at I plus 1, and the least significant digit 
							 // at I plus 2. (In other words, take the decimal representation of
							 // VX, place the hundreds digit in memory at location in I, 
							 // the tens digit at location I+1, and the ones digit at location I+2.)
					memory[I + 0] = V[x] / 100;
					memory[I + 1] = (V[x] / 10) % 10;
					memory[I + 2] = V[x] % 10;
				break;
				case 0x0055: // FX55: Stores V0 through VX in memory starting at address I 
							 // I is increased by 1 for each value written.
					for(int i = 0; i <= x; i++, I++)
						memory[I] = V[i];
				break;
				case 0x0065: // FX65: Fills V0 through VX with values from memory starting 
							 // at address I. I is increased by 1 for each value written.
					for(int i = 0; i <= x; i++, I++)
						V[i] = memory[I];
				break;
				default:
					halt();
					printf("Unknown opcode [0xF000]: 0x%x\n", opcode);
			}
		break;
		default:
			halt();
			printf("Unknown opcode: 0x%x\n", opcode);
	}

	if(!skip_pc_add_flag)
		pc += 2;

	// Update timers
	if(delay_timer > 0)
		--delay_timer;

	if(sound_timer > 0)
	{
		if(sound_timer == 1)
		{
			int duration = 64;
			double Hz = 440;

			b.beep(Hz, duration);
			b.wait();
			b.beep(Hz, duration);
			b.wait();
		}
		--sound_timer;
	}

#ifdef STATE
	printf("[ Register state ]\n");
	for(int i = 0; i < 0x10; i++)
		printf("%2.1x%c", i, (i == 0xF) ? '\n' : ' ');
	for(int i = 0; i < 0x10; i++)
		printf("%.2x%c", V[i], (i == 0xF) ? '\n' : ' ');

	printf("[ Stack state | sp: %.1x ]\n", sp);
	for(int i = 0; i < sp; i++)
		printf("%4.1x%c", i, (i == sp - 1) ? '\n' : ' ');
	for(int i = 0; i < sp; i++)
		printf("%.4x%c", stack[i], (i == sp - 1) ? '\n' : ' ');
	printf("\n");
#endif

}

void Chip8::press_key(unsigned short key_num)
{
	if(key_num != 0xFF)
	{
		key[key_num] = 1;
#ifdef DEBUG
		printf("Key press  : 0x%x\n", key_num);
#endif
		if(key_wait)
		{
			V[key_wait - 1] = key_num;
			key_wait = 0;
		}
	}

}

void Chip8::release_key(unsigned short key_num)
{
	if(key_num != 0xFF)
	{
		key[key_num] = 0;
#ifdef DEBUG
		printf("Key release: 0x%x\n", key_num);
#endif
	}
}

bool Chip8::load_game(std::string name)
{
	std::ifstream input(name, std::ios::binary);

	if(!input.is_open())
		return true;

	// Copy data to buffer
	std::vector<char> buffer((
		std::istreambuf_iterator<char>(input)), 
		(std::istreambuf_iterator<char>()));

	for(unsigned i = 0; i < buffer.size(); i++)
		memory[i + 0x200] = static_cast<unsigned char>(buffer[i]);

	return 0;
}

void Chip8::halt()
{
	halt_flag = true;
	std::cerr << "[ HALTED ]" << std::endl;
}