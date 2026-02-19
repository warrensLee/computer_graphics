
#include "fruit.h"


// constructors
Fruit::Fruit() : Entity(0.0f, 0.0f, 0.05f, 1.0f, 1.0f, 0.0f, true),
  direction(0.0f)
{
}


Fruit::Fruit(float px, float py, float rad, float red, float green, float blue, bool alive)
 : Entity(px, py, rad, red, green, blue, alive),
  direction(0.0f)
{
    vx = 0.3f;
    vy = 0.0f;
}


Fruit::~Fruit() = default;


// member methods
void Fruit::display() const
{
    if (!isAlive) 
        return;

    glColor3f(r, g, b);

    const int segments = 248;  // higher = smoother circle

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

void Fruit::setDirection(float d)
{
    direction = d;
    vx = speed * std::cos(direction);
    vy = speed * std::sin(direction);
}

void Fruit::printInformation() const
{

}

void Fruit::wrap()
{

    const float left = -1.0f + radius;
    const float right =  1.0f - radius;
    const float bottom = -1.0f + radius;
    const float top =  1.0f - radius;


    bool bouncedX = false;
    bool bouncedY = false;

    if (x > right) 
    {        
        x = right;  
        vx = -vx; 
        bouncedX = true;
    }
    if (x < left) 
    {        
        x = left;
        vx = -vx;
        bouncedX = true;
    }
    if (y > top) 
    {        
        y = top;
        vy = -vy;
        bouncedY = true;
    }
    if (y < bottom) 
    {        
        y = bottom;
        vy = -vy;
        bouncedY = true;
    }

    if (bouncedX || bouncedY)
        direction = std::atan2(vy, vx);

}



void Fruit::update(float dt)
{
    // does what every entity does... move
    x += vx * dt;
    y += vy * dt;
    
    // wrap-around (with radius so it fully leaves screen)
    wrap();

}
