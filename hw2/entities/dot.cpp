#include "dot.h"



Dot::Dot()
    : x(0.0f), y(0.0f), radius(0.05f),
      r(0.6f), g(0.0f), b(1.0f),
      isAlive(true)
{
}


Dot::Dot(float cx, float cy, float c_radius, float cr, float cg, float cb, bool c_isAlive)
    : x(cx), y(cy), radius(c_radius), r(cr), g(cg), b(cb), isAlive(c_isAlive)
{
}




void Dot::printInformation()
{

}

void Dot::setPosition(float sx, float sy)
{

}

void Dot::setColor(float sr, float sg, float sb)
{

}

void Dot::display() const
{
    if (!isAlive) return;

    glColor3f(r, g, b);

    const int segments = 64;  // higher = smoother circle

    glBegin(GL_TRIANGLE_FAN);

    // center
    glVertex2f(x, y);

    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * 3.14159265359f * i / segments;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);

        glVertex2f(x + dx, y + dy);
    }

    glEnd();
}

float Dot::getRadius() const
{
    return radius;
}

bool Dot::getAlive() const
{
    return isAlive;
}

float Dot::getR() const
{
    return r;
}

float Dot::getG() const
{
    return g;
}

float Dot::getB() const
{
    return b;
}

float Dot::getX() const
{
    return x;
}

float Dot::getY() const
{
    return y;
}

void Dot::setAlive(bool a)
{
    isAlive = a;
}
