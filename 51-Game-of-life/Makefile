CXX = g++
OBJS = main.o
LIBS = `sdl2-config --libs`
CXXFLAGS = --std=c++11 -Wall -Werror
CXXFLAGS += `sdl2-config --cflags`
EXE = life.app

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(EXE)
	@echo Build complete

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(CXXFLAGS) $(OBJS) $(LIBS)

clean:
	rm $(EXE) $(OBJS)