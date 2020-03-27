#pragma once

#include <iostream>

/** The primitive components of meshes.
 *
 * The current implementation contains these fields:
 *
 * 1) 3D Position,
 * 2) 4D Color (RGBA).
 *
 * These vertices are arranged into triangles to form meshes. */
struct Vertex
{
public:

	/** Blank vertex. */
	Vertex();


	/** Specify the positions and colors for this vertex. */
	Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a);


	/** Set the position of this vertex to the given position (x, y, z). */
	void setPosition(float x, float y, float z);


	/** Set the color of this vertex to the given RGBA color (r, g, b, a). */
	void setColor(float r, float g, float b, float a);


	/* 3D Position. */
	float x, y, z;


	/* 4D RGBA Color. */
	float r, g, b, a;


	/** Debug print. This really shouldn't be here. */
	void PrintPosition();
};
