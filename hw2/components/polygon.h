#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>
#include "vertex.h"

class Polygon
{
protected:
    std::vector<Vertex> vertices;

public:
    // constructors
    Polygon();
    Polygon(std::vector<Vertex> info);
    virtual ~Polygon() = default;

    // member functions
    void clear();
    int numVertices();
    void addVertex(const Vertex& v);

    void setPolygonColor(float a, float b, float c);
    
    virtual void printInformation() const;
    virtual void display() const;
};

#endif // POLYGON_H
