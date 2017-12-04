#include "render.h"

// Draw a vertex
void draw_vert(struct window w, struct vert v, int rev)
{
	// Center and use cartesian instead of terminal coordinates
	int y = w.h / 2 - round(v.y);
	int x = w.w / 2 + round(v.x);
	// Reverse the colors for marking
	if(rev)
		attron(A_REVERSE);

	mvprintw(y, x, ".");
	attroff(A_REVERSE);
}

// Drwa a line
void line(struct window w, struct vert from, struct vert to)
{
	// Copy x and y from vertices
	float x1 = round(from.x);
	float y1 = round(from.y);
	float x2 = round(  to.x);
	float y2 = round(  to.y);

	// Bresenham's line rasterization
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if(steep)
	{
		swap(x1, y1);
		swap(x2, y2);
	}

	if(x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int max_x = (int)x2;

	for(int x = (int)x1; x < max_x; ++x)
	{
		if(steep)
			draw_vert(w, new_vert(y, x), 0);
		else
			draw_vert(w, new_vert(x, y), 0);

		error -= dy;
		if(error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

// Draw a polygon (made up from lines)
void draw_poly(struct window w, struct vert *v[], int c)
{
	for(int i = 0; i < c; ++i)
	{
		line(w, *v[i], *v[(i + 1) % c]);
		draw_vert(w, *v[i], 0);
	}
}
