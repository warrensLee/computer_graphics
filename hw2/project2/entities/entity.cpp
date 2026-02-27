#include "entity.h"


Entity::Entity()
    : x(0.0f), y(0.0f), radius(0.05f),
      r(0.6f), g(0.0f), b(1.0f),
      isAlive(true)
{

    
}

Entity::~Entity() = default;

Entity::Entity(float cx, float cy, float c_radius, float cr, float cg, float cb, bool c_isAlive)
    : x(cx), y(cy), radius(c_radius), r(cr), g(cg), b(cb), isAlive(c_isAlive), rng(std::random_device{}())
{
    changeTimer = 0.0f;
    nextChangeTime = randFloatInRange(1.0f, 5.0f);  // change every 1–3 sec
    float angle = randFloatInRange(0.0f, 2.0f * M_PI);
    dirX = cos(angle);
    dirY = sin(angle);
}

float Entity::randFloatInRange(float low, float high)
{
    return std::uniform_real_distribution<float>{low, high}(rng);
}

int Entity::randInt(int low, int high)
{
    return std::uniform_int_distribution<int>{low, high}(rng);
}


void Entity::pickRandDirection()
{
     int r = randInt(0, 3);

    switch (r)
    {
        case 0: dirX = 1;  dirY = 0;  break;
        case 1: dirX = -1; dirY = 0;  break;
        case 2: dirX = 0;  dirY = 1;  break;
        case 3: dirX = 0;  dirY = -1; break;
    }
}


void Entity::setPosition(float sx, float sy)
{
    x = sx;
    y = sy;
}

void Entity::setColor(float sr, float sg, float sb)
{
    r = sr;
    g = sg;
    b = sb;
}

void Entity::printInformation() const
{
    std::cout << "some placeholder\n";
}

void Entity::display() const
{
    
}
//{

    // if (!isAlive) return;

    // glColor3f(r, g, b);

    // const int segments = 64;  // higher = smoother circle

    // glBegin(GL_TRIANGLE_FAN);

    // // center
    // glVertex2f(x, y);

    // for (int i = 0; i <= segments; i++)
    // {
    //     float angle = 2.0f * 3.14159265359f * i / segments;
    //     float dx = radius * cosf(angle);
    //     float dy = radius * sinf(angle);

    //     glVertex2f(x + dx, y + dy);
    // }

    // glEnd();
//}

float Entity::getRadius() const
{
    return radius;
}

bool Entity::getAlive() const
{
    return isAlive;
}

float Entity::getR() const
{
    return r;
}

float Entity::getG() const
{
    return g;
}

float Entity::getB() const
{
    return b;
}

float Entity::getX() const
{
    return x;
}

float Entity::getY() const
{
    return y;
}

void Entity::setAlive(bool a)
{
    isAlive = a;
}

void Entity::setVelocity(float nvx, float nvy)
{
    vx = nvx;
    vy = nvy;
}
void Entity::move(float dt)
{
    x += vx * dt;
    y += vy * dt;
}

void Entity::setSpeed(float s)
{
    speed = s;
}

float Entity::getSpeed() const
{
    return speed;
}

Bounds Entity::getBounds() const
{
    return { x - radius, x + radius, y - radius, y + radius };
}


// second dispatch targets
void Entity::collideWith(class Pacman&) 
{

}

void Entity::collideWith(class Ghost&) 
{

}

void Entity::collideWith(class Fruit&) 
{

}

// void Entity::collideWith(class Dot&)
// {

// }

void Entity::wrap()
{

}

void Entity::setDirection(float radians)
{
    direction = radians;
    vx = speed * std::cos(direction);
    vy = speed * std::sin(direction);

}


void Entity::update(float dt)
{
    move(dt);
    wrap();

}