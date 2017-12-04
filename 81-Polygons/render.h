#ifndef RENDER_H
#define RENDER_H

#include <ncurses/ncurses.h>
#include <math.h>

#include "polygon.h"

#define swap(x, y) do { typeof(x) swap = x; x = y; y = swap; } while (0)

struct window { int h, w; };

void line(struct window w, struct vert a, struct vert b);
void draw_vert(struct window w, struct vert v, int rev);
void draw_poly(struct window w, struct vert *v[], int c);

#endif
