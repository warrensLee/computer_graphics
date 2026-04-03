/******************************************************************************************
 *  File Name:      scene.cpp
 *  Author:         Warren Roberts
 *  Created:        March 25, 2026
 *  Last Modified:  April 1, 2026
 *
 *  Description:
 *  This is where objects are created and added to a collection of objects
 *  that will be rendered in this project.
 *
 *  Dependencies:
 *  scene.h
 *
 *  Notes:
 *  Unique pointer is used to allow polymorphism in the future, allowing
 *  for a more streamlined OOP structured space.
 *
 ******************************************************************************************/

#include "scene.h"

// this is where we use methods to create objects
// that will be on screen, adding them to a unique
// pointer vector for future expansion

Scene::Scene()
{
    // use auto because we have multiple types
    // of objects, and we want to avoid repeating
    // the type.
    auto cube = std::make_unique<Cube>();
    cube->setTexture(0);
    cube->setPosition(-2.0f, 0.0f, 0.0f);
    cube->setSize(2.0f, 2.0f, 2.0f);
    cube->setRotationSpeed(0.0f, 20.0f, 0.0f);
    addObject(std::move(cube));

    auto sphere = std::make_unique<Sphere>();
    sphere->setTexture(1);
    sphere->setPosition(2.0f, 0.0f, 0.0f);
    sphere->setSize(1.5f, 1.5f, 1.5f);
    sphere->setRotationSpeed(15.0f, 10.0f, 0.0f);
    addObject(std::move(sphere));
}

// add object to the unique pointer vector
void Scene::addObject(std::unique_ptr<Object3D> obj)
{
    objects.push_back(std::move(obj));
}

// returns the objects to be rendered in the
// appropriate area
const std::vector<std::unique_ptr<Object3D>> &Scene::getObjects() const
{
    return objects;
}

void Scene::update(float dt)
{
    // Update all objects
    for (auto &obj : objects)
    {
        obj->update(dt);
    }
    
    // Update cannon ball physics
    updateCannonBall(dt);
    
    // Update the position of the cannon ball object if it exists
    // For simplicity, let's assume the last object is the cannon ball
    if (ballActive && !objects.empty()) {
        // Update the last object's position to match ballX, ballY
        objects.back()->setPosition(ballX, ballY, 0.0f);
    }
}

void Scene::launchProjectile(float vx, float vy, float distance)
{
    printf("Scene::launchProjectile called with vx=%f, vy=%f, distance=%f\n", vx, vy, distance);
    
    // Start at cannon location
    ballX = 0.0f;
    ballY = 0.0f;

    // Set launch velocity (vx and vy are already scaled appropriately)
    ballVX = vx;
    ballVY = vy;

    ballActive = true;
    
    // Also, create a visual cannon ball object
    auto cannonBall = std::make_unique<Sphere>();
    // Use texture index 2 for cannonball.jpg
    int textureIndex = 2;
    printf("Setting cannon ball texture to index %d\n", textureIndex);
    cannonBall->setTexture(textureIndex);  
    cannonBall->setPosition(ballX, ballY, 0.0f);
    cannonBall->setSize(0.5f, 0.5f, 0.5f);
    cannonBall->setRotationSpeed(0.0f, 0.0f, 0.0f);
    addObject(std::move(cannonBall));
}

void Scene::updateCannonBall(float dt)
{
    if (ballActive)
    {
        ballX += ballVX * dt;
        ballY += ballVY * dt;

        ballVY += gravity * dt;

        if (ballY <= groundY)
        {
            ballY = groundY;
            ballActive = false;
            // Remove the cannon ball object when it hits the ground
            // Assuming the last object is the cannon ball
            if (!objects.empty()) {
                objects.pop_back();
            }
        }
    }
}
