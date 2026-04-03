/******************************************************************************************
 *  File Name:      scene.h
 *  Author:         Warren Roberts
 *  Created:        March 25, 2026
 *  Last Modified:  April 1, 2026
 *
 *  Description:
 *  This is where methods and data structures relevant to the scene are
 *  defined.
 *
 *  Dependencies:
 *  memory, vector, object3D, cubeObject, sphereObject
 *
 *  Notes:
 *  Unique pointer is used to allow polymorphism in the future, allowing
 *  for a more streamlined OOP structured space.
 *
 ******************************************************************************************/

#pragma once

#include "object3D.h"
#include "cubeObject.h"
#include "sphereObject.h"
#include <vector>
#include <memory> // for unique_ptr

class Scene
{
public:
    // constructors
    Scene();

    void update(float dt);

    void addObject(std::unique_ptr<Object3D> obj);

    void launchProjectile(float vx, float vy, float distance);
    void updateCannonBall(float dt);

    const std::vector<std::unique_ptr<Object3D>> &getObjects() const;

private:
    // unique_ptr for possible polymorphism in the future
    std::vector<std::unique_ptr<Object3D>> objects;

    float ballX = 0.0f;
    float ballY = 0.0f;

    float ballVX = 0.0f;
    float ballVY = 0.0f;

    bool ballActive = false;
    float gravity = -0.02f;
    float groundY = -5.0f;
};
