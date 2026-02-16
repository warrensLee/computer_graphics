#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>
#include "vertex.h"

class Polygon
{
public:
    std::vector<Vertex> vertices;

    // Constructors
    Polygon();
    Polygon(std::vector<Vertex> info);
    virtual ~Polygon() = default;

    // Member functions
    void setPolygonColor(float a, float b, float c);
    int numVertices();
    virtual void printInformation() const;
    virtual void display() const;
};

#endif // POLYGON_H
