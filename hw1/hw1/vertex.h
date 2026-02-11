#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>

class Vertex
{
public:
    // Public data members
    float x, y, z;
    float r, g, b;

    // Constructors
    Vertex();
    Vertex(float q, float w, float a, float c, float d, float e);

    // Member functions
    void vertexInformation();
    void setPosition(float a, float b, float c);
    void setColor(float p, float l, float m);
    float getR();
    float getG();
    float getB();
    float getX();
    float getY();
    float getZ();
};

#endif // VERTEX_H
