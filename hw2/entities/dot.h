#ifndef DOT_H
#define DOT_H


#include <cmath>
#include "../components/vertex.h"
#include "../components/gl_platform.h"

class Dot
{
private:
    float radius;
    bool isAlive;
    float r, g, b, x, y;
public:
    // Constructors
    Dot();
    Dot(float cx, float cy, float c_radius, float cr, float cg, float cb, bool c_isAlive = true);

    // Member functions
    void dotInformation();
    void setPosition(float sx, float sy);
    void setColor(float sr, float sg, float sb);
    void display() const;
    float getR() const;
    float getG() const;
    float getB() const;
    float getX() const;
    float getY() const;
    float getRadius() const;
    bool getAlive() const;

};

#endif // DOT_H
