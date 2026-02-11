#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>
#include "vertex.h" // NOT the .cpp
#include <GL/gl.h>
#include <GL/freeglut.h>

class Polygon : public Vertex
{
public:
    std::vector<Vertex> vertices;

    // Constructors
    Polygon();
    Polygon(std::vector<Vertex> info);

    // Member functions
    void setPolygonColor(float a, float b, float c);
    int numVertices();
    void polygonInformation();
    void display();
};

#endif // POLYGON_H
