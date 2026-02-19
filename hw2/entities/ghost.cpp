
#include "ghost.h"


// constructors
Ghost::Ghost() : Entity(0.0f, 0.0f, 0.05f, 1.0f, 1.0f, 0.0f, true),
  direction(0.0f)
{
}


Ghost::Ghost(float px, float py, float rad, float red, float green, float blue, bool alive)
 : Entity(px, py, rad, red, green, blue, alive),
  direction(0.0f)
{
    vx = 0.3f;
    vy = 0.0f;
}


Ghost::~Ghost() = default;


// member methods
void Ghost::display() const
{
    // using traingle fanning I will display 360 - mouth angle of a circle
    if (!isAlive)
    {
        return;
    }

    // now set pacmans color and begin TRIANGLE FANNING
    glColor3f(r, g, b);

    glBegin(GL_TRIANGLES);
        glVertex2f(x, y + radius);   // top
        glVertex2f(x - radius, y - radius); // bottom left
        glVertex2f(x + radius, y - radius);  // bottom right
    glEnd();
    
}

void Ghost::setDirection(float d)
{
    direction = d;
    vx = speed * std::cos(direction);
    vy = speed * std::sin(direction);
}

void Ghost::printInformation() const
{

}

void Ghost::wrap()
{
    const float left   = -1.0f + radius;
    const float right  =  1.0f - radius;
    const float bottom = -1.0f + radius;
    const float top    =  1.0f - radius;

    bool bouncedX = false;
    bool bouncedY = false;

    if (x > right)  { x = right;  vx = -vx; bouncedX = true; }
    if (x < left)   { x = left;   vx = -vx; bouncedX = true; }
    if (y > top)    { y = top;    vy = -vy; bouncedY = true; }
    if (y < bottom) { y = bottom; vy = -vy; bouncedY = true; }

    if (bouncedX || bouncedY)
        direction = std::atan2(vy, vx);
}


void Ghost::update(float dt)
{
    // does what every entity does... move
    x += vx * dt;
    y += vy * dt;
    
    // wrap-around (with radius so it fully leaves screen)
    wrap();

}
