#include "polygon.h"

std::vector<Vertex> vertices; // stores each vertex that makes up the polygon

Polygon::Polygon() // default constructor
{
}

Polygon::Polygon(std::vector<Vertex> info) // real constructor
{
    vertices = info;
}

void Polygon::setPolygonColor(float sx, float sy, float sz) // set each vertex's color to make the whole polygon the same color
{
    for (Vertex &v : vertices) // iterate thru each vertex in the vector
    {
        v.setColor(sx, sy, sz); // simple set color method implemented within Vertex class
    }
}

int Polygon::numVertices()
{
    return vertices.size();
}

void Polygon::printInformation() const
{
//     std::cout << "This polygon has " << numVertices() << " vertices" << std::endl; // output how many vertices there are
//     int count = 1;                                                                 // track what vertex we are on
//     for (Vertex &v : vertices)                                                     // iterate thru each vertex in the vector
//     {
//         std::cout << "Vertex (" << count << "):" << std::endl; // output the specific vertex we are at
//         v.vertexInformation();                                 // print that vertex's information
//         count++;
//     }
    std::cout << "placeholder...\n";
}

void Polygon::display() const
{
    // float x, y, z, r, g, b;
    // glBegin(GL_POLYGON);
    // for (Vertex &v : vertices) // iterate thru each vertex in the vector
    // {
    //     x = v.getX();
    //     y = v.getY();
    //     z = v.getZ();
    //     r = v.getR();
    //     g = v.getG();
    //     b = v.getB();

    //     glColor3f(r, g, b);
    //     glVertex3f(x, y, z);
    // }
    // glEnd();
    std::cout << "placeholder...\n";

}
