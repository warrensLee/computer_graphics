#include "pacman.h"
#include "fruit.h"
#include "ghost.h"
// constructors
Pacman::Pacman() : Entity(0.0f, 0.0f, 0.05f, 1.0f, 1.0f, 0.0f, true),
  mouthAngle(50.0f),
  mouthSpeed(100.0f),
  mouthOpening(false),
  direction(0.0f)
{
}


Pacman::Pacman(float px, float py, float rad, float red, float green, float blue, bool alive)
 : Entity(px, py, rad, red, green, blue, alive),
  mouthAngle(45.0f),
  mouthSpeed(120.0f),
  mouthOpening(false),
  direction(0.0f)
{
}


Pacman::~Pacman() = default;


// member methods
void Pacman::display() const
{
    // using traingle fanning I will display 360 - mouth angle of a circle
    if (!isAlive)
    {
        return;
    }

    // convert mouth angle from degrees to radians 
    float mouthAngleRadians = mouthAngle * (PI / 180.0f);

    // bound check to keep the mouth within open / close range
    if (mouthAngleRadians > PI)
    {
        mouthAngleRadians = PI;
    }
    if (mouthAngleRadians < 0.0f)
    {
        mouthAngleRadians = 0.0f;
    }

    // this will ensure that the mouth is centered and based on direction
    float startAngle = direction + mouthAngleRadians / 2.0f;
    float endAngle = direction + 2.0f * PI - mouthAngleRadians / 2.0f;

    const int segments = 1000;        // more segments of pacman to create = more smooth

    // now set pacmans color and begin TRIANGLE FANNING
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);

    // center pacman 
    glVertex2f(x, y);

    // how big each segment is
    float angleIncrement = (endAngle - startAngle) / segments;

    for (int i = 0; i <= segments; i++)
    {
       float angle = startAngle + i * angleIncrement;
       float px = x + radius * std::cos(angle);
       float py = y + radius * std::sin(angle);

       glVertex2f(px, py);
    }
    
    glEnd();

}


void Pacman::printInformation() const
{

}

void Pacman::changeDirection(float d)
{
    direction = d;
    setVelocity(speed * std::cos(direction), speed * std::sin(direction));
}

float Pacman::getDirection() const
{
    return direction;
}

float Pacman::getMouthAngle() const                  // return current mouth angle
{
    return mouthAngle;
}

void Pacman::setMouthOpening(bool open)        // will start mouth opening by changing bool value
{
    mouthOpening = open;
}

void Pacman::setMouthAngle(float angle)        // will update the angle mouth is open for animation
{
    mouthAngle = angle;
}

bool Pacman::getHasEaten() const
{
    return hasEaten;
}

void Pacman::setHasEaten(bool h)
{
    hasEaten = h;
}

void Pacman::collideWith(class Pacman& p)
{

}

void Pacman::collideWith(class Ghost& g)
{
     std::cout << "Pacman collides with ghost\n";
     if (hasEaten)
     {
        g.setAlive(false);
        ghostsAte += 1;
        return;
     }
     if (!hurt)
     {
        hurt = true;
        hurtTimer = 0.0f;      // start the cooldown window
        currentLives -= 1;
     }
}

void Pacman::collideWith(class Fruit& f)
{
    std::cout << "Pacman collides with fruit\n";
    hasEaten = true;
    powerTimer = 0.0f;  // reset timer
    f.setAlive(false);

}

void Pacman::setAlive(bool a)
{
    isAlive = a;
}

int Pacman::getLives() const
{
    return currentLives;
}

bool Pacman::getPower() const
{
    return hasEaten;
}
bool Pacman::getHurt() const
{
    return hurt;
}

int Pacman::getGhostsAte() const
{
    return ghostsAte;
}

void Pacman::wrap()
{
    // wrap horizontally
    if (x > 1.0f + radius)
        x = -1.0f - radius;
    else if (x < -1.0f - radius)
        x = 1.0f + radius;
    // wrap vertically
    if (y > 1.0f + radius)
        y = -1.0f -  radius;
    else if (y < -1.0f - radius)
        y = 1.0f + radius;
}
void Pacman::setMouseTarget(float mx, float my)
{
    hasMouseTarget = true;
    targetX = mx;
    targetY = my;
}


void Pacman::update(float dt)
{
    // if game over
    if(currentLives <= 0)
    {
        setAlive(false);
    }

    // timers and modes
    if (hurt) 
    {
        hurtTimer += dt;
        if (hurtTimer >= hurtDuration) 
        {
            hurt = false;
            hurtTimer = 0.0f;
        }
    }

    if (hasEaten) 
    {
        powerTimer += dt;
        if (powerTimer >= powerDuration) 
        {
            hasEaten = false;
            powerTimer = 0.0f;
        }
    }

    // pick speed baed on how pacman is doing
    float targetSpeed = 0.4f;

    if (hasEaten) 
        targetSpeed = 0.6f;
    if (hurt)     
        targetSpeed = 0.2f;

    setSpeed(targetSpeed);

    float dx = 0.0f;
    float dy = 0.0f;

    if (hasMouseTarget)
    {
        float mx = targetX - x;
        float my = targetY - y;

        direction = std::atan2(my, mx);

        float dist = std::sqrt(mx * mx + my * my);

        if (dist < 0.02f)   // stop threshold
        {
            hasMouseTarget = false;
            vx = 0.0f;
            vy = 0.0f;
        }
        else
        {
            float move = speed * dt;

            // clamp so we don’t overshoot
            if (move > dist)
                move = dist;

            x += (mx / dist) * move;
            y += (my / dist) * move;
            vx = 0.0f;
            vy = 0.0f;
        }
    }
    else
    {
        if (moveUp)
        {
            dy += 1.0f;
        }
        if (moveDown)
        {
            dy -= 1.0f;
        }  
        if (moveRight)
        {
            dx += 1.0f;
        } 
        if (moveLeft)
        {
            dx -= 1.0f;
        }  

        // normalize so diagonal isn't faster
        float length = std::sqrt(dx * dx + dy * dy);
        if (length > 0.0f)
        {
            dx /= length;
            dy /= length;

            vx = dx * speed;
            vy = dy * speed;

            direction = std::atan2(dy, dx);
        }
        else
        {
            vx = 0.0f;
            vy = 0.0f;
        }
    }
    
    // does what every entity does... move
    Entity::update(dt);

    // pacman has special wrapping and goes from one side to the other
    wrap();

    // clamp mouth openings
    const float minMouth = 0.0f;
    const float maxMouth = 65.0f;


    if (moveUp || moveDown || moveLeft || moveRight || hasMouseTarget)
    {
        // if it is time to open the mouth 
        if (mouthOpening)
        {
            mouthAngle += mouthSpeed * dt;
        }
        else
        {
            mouthAngle -= mouthSpeed * dt;
        }


        if (mouthAngle >= maxMouth) 
        { 
            mouthAngle = maxMouth; 
            mouthOpening = false; 
        }
        if (mouthAngle <= minMouth) 
        { 
            mouthAngle = minMouth; 
            mouthOpening = true;  
        }
    }
    else
    {
        mouthAngle += mouthSpeed * dt;
        if (mouthAngle > maxMouth)
            mouthAngle = maxMouth;
        mouthOpening = true;
    }
}
