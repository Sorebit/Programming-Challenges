#include <stdarg.h>
#include <math.h>

#include "polygon.h"

struct vert new_vert(float x, float y)
{
	struct vert v;
	v.x = x;
	v.y = y;
	return v;
}

// Polygon
void new_poly(struct vert pool[], struct vert *p[], int c, ...)
{
	// Get c pointers to vertices from argument list
	va_list args; 
	va_start(args, c);

	for(int i = 0; i < c; ++i)
		p[i] = &pool[va_arg(args, int)];

	va_end(args);
}

// Translate polygon
void translate(struct vert *p[], int c, float x, float y)
{
	// Add x translation to x and y to y
	for(int i = 0; i < c; ++i)
	{
		p[i]->x += x;
		p[i]->y += y;
	}
}

// Rotate polygon
void rotate(struct vert *p[], int c, struct vert o, int angle)
{
	// Angles to radians
	float theta = (float)((angle*M_PI)/180);
	// New x and y
	float nx, ny;
	// Temporary x and y for translation
	float x, y;

	for(int i = 0; i < c; ++i)
	{
		// Move pivot point (struct vert o) to 0, 0
		x = p[i]->x - o.x;
		y = p[i]->y - o.y;
		// Rotate around 0, 0 using the rotation matrix (t is theta)
		// cos(t)  -sin(t)
		// sin(t)   cos(t)
		nx = x*cos(theta) - y*sin(theta);
		ny = x*sin(theta) + y*cos(theta);
		// Move pivot point (struct vert o) back to its place
		p[i]->x = nx + o.x;
		p[i]->y = ny + o.y;
	}
}

// Scale polygon
void scale(struct vert *p[], int c, float scale)
{
	// Multiply x and y by scale
	for(int i = 0; i < c; ++i)
	{
		p[i]->x *= scale;
		p[i]->y *= scale;
	}
}
