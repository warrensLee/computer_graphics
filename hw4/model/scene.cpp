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
    // Create objects at appropriate positions
    auto cube = std::make_unique<Cube>();
    cube->setTexture(0);
    cube->setPosition(-5.0f, -2.0f, 0.0f);
    cube->setSize(2.0f, 2.0f, 2.0f);
    cube->setRotationSpeed(0.0f, 20.0f, 0.0f);
    addObject(std::move(cube));

    auto sphere = std::make_unique<Sphere>();
    sphere->setTexture(1);
    sphere->setPosition(5.0f, -2.0f, 0.0f);
    sphere->setSize(2.0f, 2.0f, 2.0f);
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
    
    // Update cannon balls physics
    updateCannonBalls(dt);
}

void Scene::launchProjectile(float vx, float vy, float distance, float spawnX, float spawnY)
{
    // Check if we can launch more cannonballs
    int activeCount = 0;
    for (const auto& cb : cannonBalls) {
        if (cb.active) activeCount++;
    }
    
    if (activeCount >= Config::MAX_ACTIVE_CANNONBALLS) {
        printf("Cannot launch cannonball: maximum active cannonballs (%d) reached. Wait for some to hit the ground.\n", 
            Config::MAX_ACTIVE_CANNONBALLS);
        return;
    }
    
    printf("Scene::launchProjectile called with vx=%f, vy=%f, distance=%f, spawn=(%f, %f)\n", vx, vy, distance, spawnX, spawnY);
    
    // start at click location, but ensure it's at a reasonable height
    float ballX = spawnX;
    float ballY = spawnY;
    
    // if spawn position is too low, adjust it
    if (ballY < groundY + 1.0f) {
        ballY = groundY + 2.0f;  // Well above ground
    }
    
    // ensure it's not too high
    if (ballY > 5.0f) {
        ballY = 5.0f;
    }
    
    float ballZ = 0.0f;

    // create a cannon ball object
    auto cannonBall = std::make_unique<Sphere>();

    // use texture index 2 for cannonball.jpg
    int textureIndex = 2;
    printf("Setting cannon ball texture to index %d\n", textureIndex);
    cannonBall->setTexture(textureIndex);  
    cannonBall->setPosition(ballX, ballY, ballZ);
    cannonBall->setSize(Config::CANNONBALL_WIDTH, Config::CANNONBALL_HEIGHT, Config::CANNONBALL_DEPTH);
    cannonBall->setRotationSpeed(0.2f, 0.2f, 0.2f);
    
    // Add to objects vector and get its index
    std::size_t objectIndex = objects.size();
    addObject(std::move(cannonBall));
    
    // Add to cannonBalls tracking
    CannonBall cb;
    cb.x = ballX;
    cb.y = ballY;
    cb.vx = vx;
    cb.vy = vy;
    cb.active = true;
    cb.objectIndex = objectIndex;
    cannonBalls.push_back(cb);
}

void Scene::updateCannonBalls(float dt)
{
    // Update each cannonball
    for (auto it = cannonBalls.begin(); it != cannonBalls.end(); ) {
        if (it->active) {
            // Update position
            it->x += it->vx * dt;
            it->y += it->vy * dt;
            
            // Update velocity with gravity
            it->vy += gravity * dt;
            
            // Check if hit ground
            if (it->y <= groundY) {
                it->y = groundY;
                it->active = false;
                
                // Remove the corresponding object from the objects vector
                if (it->objectIndex < objects.size()) {
                    // Move to end and pop
                    if (it->objectIndex != objects.size() - 1) {
                        std::swap(objects[it->objectIndex], objects.back());
                        // Update the index of the cannonball that was swapped
                        // Find the cannonball that references the object we just swapped
                        for (auto& cb : cannonBalls) {
                            if (cb.objectIndex == objects.size() - 1) {
                                cb.objectIndex = it->objectIndex;
                                break;
                            }
                        }
                    }
                    objects.pop_back();
                }
                printf("Cannon ball hit the ground and was removed\n");
                
                // Remove from cannonBalls vector
                it = cannonBalls.erase(it);
                continue;
            }
            
            // Update the corresponding object's position
            if (it->objectIndex < objects.size()) {
                objects[it->objectIndex]->setPosition(it->x, it->y, 0.0f);
            }
            ++it;
        } else {
            // Remove inactive cannonballs
            it = cannonBalls.erase(it);
        }
    }
}
