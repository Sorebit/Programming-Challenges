// Brainfuck interpreter
// Written as part of /g/'s programming challenge
//
// Heavily inspired by kgabis' implememtation (https://github.com/kgabis)
// Sorebit - https://github.com/Sorebit/
//
// Reference: https://en.wikipedia.org/wiki/Brainfuck
//
// Usage: ./bf filename

#include <stdio.h>

#define PRG_END         0

#define SUCCESS         0
#define FAILURE         1

#define PROGRAM_SIZE    4096
#define STACK_SIZE      512
#define DATA_SIZE       65535

// Stack type
struct Stack_t {
	int size;
	int data[STACK_SIZE];
};
inline void Stack_push(struct Stack_t* S, int el) { S->data[S->size++] = el; }
inline void Stack_pop(struct Stack_t* S) { S->size--; }
inline int Stack_top(struct Stack_t* S) { return S->data[S->size - 1]; }
inline int Stack_empty(struct Stack_t* S) { return S->size == 0; }
inline int Stack_full(struct Stack_t* S) { return S->size == STACK_SIZE; }

char op[PROGRAM_SIZE]; // operators
unsigned int jmp[PROGRAM_SIZE]; // jumps

struct Stack_t stack;

int compile(FILE* fp)
{
	unsigned short pc = 0, jmp_pc;
	int c;
	while((c = getc(fp)) != EOF && pc < PROGRAM_SIZE)
	{
		switch (c)
		{
			// Straight-forward operators
			case '>': case '<': case '+':
			case '-': case '.': case ',': 
				op[pc] = c;
				break;
			case '[':
				op[pc] = c;
				if(Stack_full(&stack))
				{
					fprintf(stderr, "Stack overflow!\n");
					return FAILURE;
				}
				// Push loop to stack so we know which jump to use
				Stack_push(&stack, pc);
				break;
			case ']':
				if(Stack_empty(&stack))
				{
					fprintf(stderr, "Stack underflow!\n");
					return FAILURE;
				}
				// Save jump from stack to jmp
				jmp_pc = Stack_top(&stack);
				Stack_pop(&stack);
				op[pc] = c;
				jmp[pc] = jmp_pc;
				jmp[jmp_pc] = pc;
				break;
			default: pc--; break;
		}
		pc++;
	}
	if(pc == PROGRAM_SIZE)
	{
		fprintf(stderr, "Input file too large!\n");
		return FAILURE;
	}
	if(!Stack_empty(&stack))
	{
		fprintf(stderr, "Stack not empty at end of execution!\n");
		return FAILURE;
	}
	op[pc] = PRG_END;
	return SUCCESS;
}

int execute()
{
	// Allocate memory tape and pointer
	unsigned int data[DATA_SIZE], pc = 0;
	unsigned int ptr = DATA_SIZE;
	// Clear memory tape
	while(--ptr) { data[ptr] = 0; }
	// Loop through program
	while(op[pc] != PRG_END && ptr < DATA_SIZE)
	{
		switch (op[pc])
		{
			case '>': ptr++; break;
			case '<': ptr--; break;
			case '+': data[ptr]++; break;
			case '-': data[ptr]--; break;
			case '.': putchar(data[ptr]); break;
			case ',': data[ptr] = (unsigned int)getchar(); break;
			case '[': if(!data[ptr]) { pc = jmp[pc]; } break;
			case ']': if(data[ptr]) { pc = jmp[pc]; } break;
			default: return FAILURE;
		}
		pc++;
	}

	// I used this for debugging and found it useful while creating /examples/multiply.bf
	// printf("\n");
	// for(int i = 0; i < 10; i++) printf("%d ", data[i]);
	// printf("\n");

	return (ptr != DATA_SIZE ? SUCCESS : FAILURE);
}

int main(int argc, const char * argv[])
{
	int status;
	FILE *fp;
	// Open file specified as argument
	if(argc != 2 || (fp = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return FAILURE;
	}

	// Compile and close file
	status = compile(fp);
	fclose(fp);

	// Execute
	if(status == SUCCESS) status = execute();
	if(status == FAILURE) fprintf(stderr, "Execution error!\n");
	return status;
}
