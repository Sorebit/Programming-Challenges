CXX = g++
OBJS = main.o chip8.o graphics.o beeper.o
LIBS = `sdl2-config --libs`
CXXFLAGS = --std=c++11 -Wall -Werror
CXXFLAGS += `sdl2-config --cflags`
EXE = chip8emu.app

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

all: $(EXE)
	@echo Build complete

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS) $(LIBS)

clean:
	rm $(EXE) $(OBJS)

