/******************************************************************************************
 *  File Name:      cannonBall.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 3, 2026
 *
 *  Description:
 *  Defines the Cube class, a textured cube object that inherits from Object3D.

 *  Dependencies:
 *  object3D.h
 * 
 *  Notes:
 *
 ******************************************************************************************/

#pragma once

#include "object3D.h"
#include <memory>

class CannonBall;

class Cube : public Object3D
{
public:
    void draw(Render& renderer) const override;

    void launchProjectile(float vx, float vy, float distance, float spawnX, float spawnY);
    void updateCannonBalls(float dt);

};
