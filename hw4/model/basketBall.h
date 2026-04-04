/******************************************************************************************
 *  File Name:      BasketBall.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 3, 2026
 *
 *  Description:
 *  Defines the BasketBall class, which inherits from Sphere and adds
 *  projectile behavior such as launching, gravity, bounce, and active state.
 *
 *  Dependencies:
 *  sphereObject.h
 *
 ******************************************************************************************/

#pragma once

#include "sphereObject.h"

class BasketBall : public Sphere
{
public:
    BasketBall();

    void draw(Render& renderer) const override;
    void update(float dt) override;

    void launch(float vx, float vy, float spawnX, float spawnY);
    bool isActive() const;

private:
    void handleWallBounce();
    void setRandomSpin(float vx, float vy);

    bool active = false;

    float gravity = -2.0f;
    float groundY = -5.0f;
};