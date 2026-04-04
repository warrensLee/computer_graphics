/******************************************************************************************
 *  File Name:      basketball.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 3, 2026
 *
 *  Description:
 *  Implements the Basketball class, including launch behavior, gravity,
 *  bounce physics, and active state. This allows the scene to interact
 *  with basketball objects while maintaining clean OOP design.
 *
 *  Dependencies:
 *  basketball.h
 *  render.h
 *  config.h
 *
 ******************************************************************************************/

#include "basketBall.h"
#include "../view/render.h"
#include "../core/config.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

void BasketBall::draw(Render& renderer) const
{
    renderer.drawSphere(*this);
}

BasketBall::BasketBall()
{
    static bool seeded = false;
    if (!seeded)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    // use basketball texture and size
    setTexture(2);
    setSize(Config::BASKETBALL_WIDTH, Config::BASKETBALL_HEIGHT, Config::BASKETBALL_DEPTH);
}

void BasketBall::launch(float vx, float vy, float spawnX, float spawnY)
{
    float ballY = spawnY;

    // ensure ball starts above the ground
    if (ballY < groundY + 1.0f)
    {
        ballY = groundY + 2.0f;
    }

    // limit maximum spawn height
    if (ballY > 5.0f)
    {
        ballY = 5.0f;
    }

    setPosition(spawnX, ballY, 0.0f);
    setVelocity(vx, vy, 0.0f);
    setRandomSpin(vx, vy);

    active = true;
}

void BasketBall::update(float dt)
{
    if (!active)
        return;

    // get position and velocity
    float x = getX();
    float y = getY();
    float vx = getVX();
    float vy = getVY();

    // apply motion and gravity
    x += vx * dt;
    y += vy * dt;
    vy += gravity * dt;

    setPosition(x, y, 0.0f);
    setVelocity(vx, vy, 0.0f);

    handleWallBounce();

    // stop ball when it hits the ground
    if (getY() <= groundY)
    {
        setPosition(getX(), groundY, 0.0f);
        active = false;
    }

    // update rotation (spin)
    float rx = getRotX();
    float ry = getRotY();
    float rz = getRotZ();

    // apply rotation speed to rotation angles
    rx += getRotVX() * dt;
    ry += getRotVY() * dt;
    rz += getRotVZ() * dt;

    setRotation(rx, ry, rz);
}

void BasketBall::handleWallBounce()
{
    float x = getX();
    float y = getY();
    float vx = getVX();
    float vy = getVY();

    float radius = getWidth() * 0.5f;

    float leftWall = -9.3f;
    float rightWall = 9.3f;
    float bottomWall = -13.0f;
    float topWall = 13.0f;

    bool bounced = false;

    if (x - radius <= leftWall)
    {
        x = leftWall + radius;
        vx = -vx * 0.85f;
        bounced = true;
    }
    else if (x + radius >= rightWall)
    {
        x = rightWall - radius;
        vx = -vx * 0.85f;
        bounced = true;
    }

    if (y - radius <= bottomWall)
    {
        y = bottomWall + radius;
        vy = -vy * 0.85f;
        bounced = true;
    }
    else if (y + radius >= topWall)
    {
        y = topWall - radius;
        vy = -vy * 0.85f;
        bounced = true;
    }

    setPosition(x, y, 0.0f);
    setVelocity(vx, vy, 0.0f);

    if (bounced)
    {
        float rotX = getRotVX();
        float rotY = getRotVY();
        float rotZ = getRotVZ();

        rotZ *= 0.92f;
        rotX *= 0.8f;
        rotY *= 0.8f;

        rotX += static_cast<float>((rand() % 11) - 5);
        rotY += static_cast<float>((rand() % 11) - 5);

        setRotationSpeed(rotX, rotY, rotZ);
    }
}

void BasketBall::setRandomSpin(float vx, float vy)
{
    float speed = std::sqrt(vx * vx + vy * vy);

    // main basketball spin
    float rotZ = 20.0f + speed * 120.0f;

    // subtle wobble only
    float rotX = static_cast<float>((rand() % 21) - 10);
    float rotY = static_cast<float>((rand() % 21) - 10);

    if (vx < 0.0f)
    {
        rotZ = -rotZ;
    }

    setRotationSpeed(rotX, rotY, rotZ);
}

bool BasketBall::isActive() const
{
    return active;
}