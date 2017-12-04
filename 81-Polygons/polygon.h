#ifndef POLYGON_H
#define POLYGON_H

// Vertex
struct vert { float x, y; };
struct vert new_vert(float x, float y);

// Polygons are just an array of vertices
void new_poly(struct vert pool[], struct vert *v[], int c, ...);

// Transformations
void translate(struct vert *p[], int c, float x, float y);
void rotate(struct vert *p[], int c, struct vert o, int angle);
void scale(struct vert *p[], int c, float scale);

#endif