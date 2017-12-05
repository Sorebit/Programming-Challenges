CXX = g++
OBJS = main.o chip8.o graphics.o audio.o
LIBS = `sdl2-config --libs`
CXXFLAGS = --std=c++11 -Wall -Werror
CXXFLAGS += `sdl2-config --cflags` -lSDL2_mixer
EXE = chip8emu.app

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

all: $(EXE)
	@echo Build complete

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS) $(LIBS)

rmobj:
	rm $(OBJS)

clean:rmobj
	rm $(EXE)
