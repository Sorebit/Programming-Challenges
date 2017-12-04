// Define, translate and rotate polygon
// Written as part of Programming Challenges
//
// Sorebit - https://github.com/Sorebit/
//
// Controls:
// - wsad to move polygon around
// - j to rotate counter-clockwise by 10 degrees around pivot point p
// - l to rotate clockwise by 10 degrees around pivot point p
// - i to scale up with a scale of 1.5
// - k to scale down with a scale of 1.5 (scale = 0.75)
// - q to quit
//
// Dependencies:
// - ncurses
//
// Notes:
// - I believe the rounding doesn't deform anything
//   because it changes very little (6th decimal place)

#include <stdio.h>
#include <math.h>

#include "polygon.h"
#include "render.h"

int main(int argc, char const *argv[])
{
	// Window
	struct window win;

	// Vertices
	struct vert vertices[7];
	// 0,0
	vertices[0] = new_vert(  0.0,   0.0);
	// Polygon
	vertices[1] = new_vert( 15.0,   9.0);
	vertices[2] = new_vert(  0.0,  14.0);
	vertices[3] = new_vert(-15.0,   9.0);
	vertices[4] = new_vert(-15.0, - 7.0);
	vertices[5] = new_vert(  0.0, -12.0);
	vertices[6] = new_vert( 15.0, - 7.0);

	initscr();
	getmaxyx(stdscr, win.h, win.w);
	noecho();
	curs_set(0);

	// 0,0
	struct vert pivot = new_vert(-5.0, 5.0);
	draw_vert(win, pivot, 1);

	// Simple triangle
	const int c = 6;
	struct vert *v[c];
	new_poly(vertices, v, c, 1, 2, 3, 4, 5, 6);
	draw_poly(win, v, c);

	char key = 0;
	while((key = getch()) != 'q')
	{
		// Clear the screen
		clear();

		// Translate controls
		if(key == 'a') translate(v, c, -1, 0);
		if(key == 'd') translate(v, c, 1, 0);
		if(key == 'w') translate(v, c, 0, 1);
		if(key == 's') translate(v, c, 0, -1);
		// Rotate controlsl
		if(key == 'j') rotate(v, c, pivot, 10);
		if(key == 'l') rotate(v, c, pivot, -10);
		// Scale controls
		if(key == 'i') scale(v, c, 1.5);
		if(key == 'k') scale(v, c, 0.75);

		// Draw
		draw_poly(win, v, c);
		draw_vert(win, pivot, 1);
	}

	curs_set(1);
	endwin();
}
