#pragma once

#include <iostream>

// colored vertices used to build models.
struct Vertex
{
public:

	Vertex();
	Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a);

	// setters:
	void setPosition(float x, float y, float z);
	void setColor(float r, float g, float b, float a);

	float x, y, z;
	float r, g, b, a;

	// debug:
	void PrintPosition();
};
