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
#include <cstdlib>
#include <ctime>

// this is where we use methods to create objects
// that will be on screen, adding them to a unique
// pointer vector for future expansion

Scene::Scene()
{
    // Seed random number generator for random rotation speeds
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
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
    
    // update cannon balls physics
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
    if (ballY < groundY + 1.0f) 
    {
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

    // give each cannonball random rotation speeds for more realistic spinning
    float rotX = 100.0f + static_cast<float>(std::rand() % 200);  // 100-300 degrees/sec
    float rotY = 80.0f + static_cast<float>(std::rand() % 200);   // 80-280 degrees/sec  
    float rotZ = 60.0f + static_cast<float>(std::rand() % 150);   // 60-210 degrees/sec
    
    // Make the rotation speed proportional to launch velocity for more realism
    float speedFactor = sqrt(vx*vx + vy*vy) / 5.0f;
    if (speedFactor > 0.5f) {
        rotX *= speedFactor;
        rotY *= speedFactor;
        rotZ *= speedFactor;
    }
    
    // Ensure minimum rotation speed
    if (rotX < 100.0f) rotX = 100.0f;
    if (rotY < 80.0f) rotY = 80.0f;
    if (rotZ < 60.0f) rotZ = 60.0f;
    
    printf("Setting cannonball rotation speed: (%.1f, %.1f, %.1f) degrees/sec\n", rotX, rotY, rotZ);
    cannonBall->setRotationSpeed(rotX, rotY, rotZ);
    
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
    // iterate thru each cannonball
    for (auto it = cannonBalls.begin(); it != cannonBalls.end(); ) {
        if (it->active) {
            // change position
            it->x += it->vx * dt;
            it->y += it->vy * dt;
            
            // change velocity with gravity
            it->vy += gravity * dt;
            
            // Check for wall collisions before ground check
            // Use reasonable wall boundaries that match the visible area
            float wallBoundaryX = 10.0f;  // Visible area is about ±9
            float wallBoundaryY = 10.0f;  // Same for y
            
            bool bounced = false;
            
            // Check left/right walls (x boundaries)
            if (it->x <= -wallBoundaryX) {
                it->x = -wallBoundaryX;  // Push back inside
                it->vx = -it->vx * 0.7f;  // Reverse x direction and reduce speed
                bounced = true;
                printf("Cannonball hit LEFT wall at x=%.2f\n", it->x);
            } else if (it->x >= wallBoundaryX) {
                it->x = wallBoundaryX;   // Push back inside
                it->vx = -it->vx * 0.7f;  // Reverse x direction and reduce speed
                bounced = true;
                printf("Cannonball hit RIGHT wall at x=%.2f\n", it->x);
            }
            
            // Check front/back walls (y boundaries) - in our 2D view, y is the other horizontal axis
            if (it->y <= -wallBoundaryY) {
                it->y = -wallBoundaryY;  // Push back inside
                it->vy = -it->vy * 0.7f;  // Reverse y direction and reduce speed
                bounced = true;
                printf("Cannonball hit BOTTOM wall at y=%.2f\n", it->y);
            } else if (it->y >= wallBoundaryY) {
                it->y = wallBoundaryY;   // Push back inside
                it->vy = -it->vy * 0.7f;  // Reverse y direction and reduce speed
                bounced = true;
                printf("Cannonball hit TOP wall at y=%.2f\n", it->y);
            }
            
            if (bounced) {
                printf("Cannonball bounced at (%.2f, %.2f) with velocity (%.2f, %.2f)\n", 
                       it->x, it->y, it->vx, it->vy);
                // Apply additional energy loss for realism
                it->vx *= 0.9f;
                it->vy *= 0.9f;
            }
            
            // check if hit ground
            if (it->y <= groundY) 
            {
                it->y = groundY;
                it->active = false;
                
                // now remove the corresponding object from the objects vector
                if (it->objectIndex < objects.size()) 
                {
                    // move to end and pop
                    if (it->objectIndex != objects.size() - 1) 
                    {
                        std::swap(objects[it->objectIndex], objects.back());
                        // update the index of the cannonball that was swapped
                        // find the cannonball that references the object we just swapped
                        for (auto& cb : cannonBalls) 
                        {
                            if (cb.objectIndex == objects.size() - 1) 
                            {
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
