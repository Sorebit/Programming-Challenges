CC     ?= gcc
CFLAGS ?= -O2 -Wall -pedantic
FILES  ?= main.c polygon.c render.c
CLIBS  ?= -lncurses -lm
NAME   ?= polygons

all:
	$(CC) $(CFLAGS) $(FILES) -o $(NAME).app $(CLIBS)
