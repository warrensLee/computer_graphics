/******************************************************************************************
 *  File Name:      scene.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 3, 2026
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
#include "../core/config.h"
#include "cubeObject.h"
#include "sphereObject.h"
#include "basketBall.h"
#include <vector>
#include <memory> // for unique_ptr

class Scene
{
public:
    // constructors
    Scene();

    void update(float dt);

    void addObject(std::unique_ptr<Object3D> obj);

    void launchProjectile(float vx, float vy, float distance, float spawnX = 0.0f, float spawnY = 0.0f);
    void updateBasketBalls(float dt);

    const std::vector<std::unique_ptr<Object3D>> &getObjects() const;

private:
    // unique_ptr for possible polymorphism in the future
    std::vector<std::unique_ptr<Object3D>> objects;
    
    float gravity = -2.0f;      
    float groundY = -5.0f;
};
