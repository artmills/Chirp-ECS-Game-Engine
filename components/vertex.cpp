#include "vertex.hpp"

Vertex::Vertex() {}
Vertex::Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a)
	: x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), a(_a) {}


void Vertex::setPosition(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
void Vertex::setColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Vertex::PrintPosition()
{
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}
