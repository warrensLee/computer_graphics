#include "vertex.h"

float x, y, z, r, g, b;

Vertex::Vertex()
{
}

Vertex::Vertex(float vx, float vy, float vz, float vr, float vg, float vb)
{
    x = vx, y = vy, z = vz, r = vr, g = vg, b = vb;
}

void Vertex::vertexInformation() const
{
    std::cout << "Position(X, Y, Z) => Position(" << x << ", " << y << ", " << z << ")" << std::endl;
    std::cout << "Color(R, G, B) => Color(" << r << ", " << g << ", " << b << ")" << std::endl;
}

//  “set” methods that allow the user to store (x,y,z) values for each
//   point and the (R,G,B) value
void Vertex::setPosition(float sx, float sy, float sz)
{
    x = sx, y = sy, z = sz;
}

void Vertex::setColor(float sr, float sg, float sb)
{
    r = sr, g = sg, b = sb;
}

float Vertex::getR() const
{
    return r;
}

float Vertex::getG() const
{
    return g;
}

float Vertex::getB() const
{
    return b;
}

float Vertex::getX() const
{
    return x;
}

float Vertex::getY() const
{
    return y;
}

float Vertex::getZ() const
{
    return z;
}
