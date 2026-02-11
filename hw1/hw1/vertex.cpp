#include "vertex.h"

float x, y, z, r, g, b;

Vertex::Vertex()
{
}

Vertex::Vertex(float q, float w, float a, float c, float d, float e)
{
    x = q, y = w, z = a, r = c, g = d, b = e;
}

void Vertex::vertexInformation()
{
    std::cout << "Position(X, Y, Z) => Position(" << x << ", " << y << ", " << z << ")" << std::endl;
    std::cout << "Color(R, G, B) => Color(" << r << ", " << g << ", " << b << ")" << std::endl;
}

//  “set” methods that allow the user to store (x,y,z) values for each
//   point and the (R,G,B) value
void Vertex::setPosition(float a, float b, float c)
{
    x = a, y = b, z = c;
}

void Vertex::setColor(float p, float l, float m)
{
    r = p, g = l, b = m;
}

float Vertex::getR()
{
    return r;
}

float Vertex::getG()
{
    return g;
}

float Vertex::getB()
{
    return b;
}

float Vertex::getX()
{
    return x;
}

float Vertex::getY()
{
    return y;
}

float Vertex::getZ()
{
    return z;
}
