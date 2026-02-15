#ifndef DOT_H
#define DOT_H


#include <cmath>
#include "../components/vertex.h"

class Dot
{
private:
    float radius;
    bool isAlive;
    float r, g, b, x, y;
public:
    // constructors
    Dot();
    Dot(float cx, float cy, float c_radius, float cr, float cg, float cb, bool c_isAlive = true);

    // member functions
    void printInformation();
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
	bool setAlive(bool a) const;

};

#endif // DOT_H
