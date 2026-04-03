/******************************************************************************************
 *  File Name:      cannonBall.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 3, 2026
 *
 *  Description:
 *  Defines the Cube class, a textured cube object that inherits from Object3D.

 *  Dependencies:
 *  cannonBall.h
 * 
 *  Notes:
 *
 ******************************************************************************************/


#include "cannonBall.h"

// seed random number generator for rotation speeds
std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
void CannonBall::launchProjectile(float vx, float vy, float distance, float spawnX, float spawnY)
{
    // check if we can launch more cannonballs
    int activeCount = 0;
    for (const auto& cb : cannonBalls) {
        if (cb.active) activeCount++;
    }
    
    if (activeCount >= Config::MAX_ACTIVE_CANNONBALLS) {
        printf("cannot launch cannonball: maximum active cannonballs (%d) reached. wait for some to hit the ground.\n", 
            Config::MAX_ACTIVE_CANNONBALLS);
        return;
    }
    
    printf("scene::launchprojectile called with vx=%f, vy=%f, distance=%f, spawn=(%f, %f)\n", vx, vy, distance, spawnX, spawnY);
    
    // start at click location, adjust height if needed
    float ballX = spawnX;
    float ballY = spawnY;
    
    // ensure spawn position is above ground
    if (ballY < groundY + 1.0f) 
    {
        ballY = groundY + 2.0f;  // well above ground
    }
    
    // limit maximum height
    if (ballY > 5.0f) {
        ballY = 5.0f;
    }
    
    float ballZ = 0.0f;

    // create a cannonball object
    auto cannonBall = std::make_unique<Sphere>();

    // use texture index 2 for cannonball.jpg
    int textureIndex = 2;
    printf("setting cannon ball texture to index %d\n", textureIndex);
    cannonBall->setTexture(textureIndex);  
    cannonBall->setPosition(ballX, ballY, ballZ);
    cannonBall->setSize(Config::CANNONBALL_WIDTH, Config::CANNONBALL_HEIGHT, Config::CANNONBALL_DEPTH);

    // give each cannonball random rotation speeds for realistic spinning
    float rotX = 100.0f + static_cast<float>(std::rand() % 200);  // 100-300 degrees/sec
    float rotY = 80.0f + static_cast<float>(std::rand() % 200);   // 80-280 degrees/sec  
    float rotZ = 60.0f + static_cast<float>(std::rand() % 150);   // 60-210 degrees/sec
    
    // make rotation speed proportional to launch velocity
    float speedFactor = sqrt(vx*vx + vy*vy) / 5.0f;
    if (speedFactor > 0.5f) {
        rotX *= speedFactor;
        rotY *= speedFactor;
        rotZ *= speedFactor;
    }
    
    // ensure minimum rotation speed
    if (rotX < 100.0f) rotX = 100.0f;
    if (rotY < 80.0f) rotY = 80.0f;
    if (rotZ < 60.0f) rotZ = 60.0f;
    
    printf("setting cannonball rotation speed: (%.1f, %.1f, %.1f) degrees/sec\n", rotX, rotY, rotZ);
    cannonBall->setRotationSpeed(rotX, rotY, rotZ);
    
    // add to objects vector and get its index
    std::size_t objectIndex = objects.size();
    addObject(std::move(cannonBall));
    
    // add to cannonballs tracking
    CannonBall cb;
    cb.x = ballX;
    cb.y = ballY;
    cb.vx = vx;
    cb.vy = vy;
    cb.active = true;
    cb.objectIndex = objectIndex;
    cannonBalls.push_back(cb);
}

void CannonBall::updateCannonBalls(float dt)
{
    // iterate through each cannonball
    for (auto it = cannonBalls.begin(); it != cannonBalls.end(); ) {
        if (it->active) {
            // update position
            it->x += it->vx * dt;
            it->y += it->vy * dt;
            
            // apply gravity to vertical velocity
            it->vy += gravity * dt;
            
            // get cannonball radius (half of width)
            float radius = Config::CANNONBALL_WIDTH * 0.5f;
            
            // wall boundaries (fixed positions)
            float leftWall = -9.3f;
            float rightWall = 9.3f;
            float bottomWall = -13.0f;
            float topWall = 13.0f;
            
            bool bounced = false;
            
            // check left wall collision (x boundary)
            if (it->x - radius <= leftWall) {
                it->x = leftWall + radius;         // push back to just touching the wall
                it->vx = -it->vx * 0.85f;           // reverse x direction with energy loss
                bounced = true;
                printf("cannonball hit left wall at x=%.2f\n", it->x);
            } 
            // check right wall collision
            else if (it->x + radius >= rightWall) {
                it->x = rightWall - radius;        // push back to just touching the wall
                it->vx = -it->vx * 0.85f;           // reverse x direction with energy loss
                bounced = true;
                printf("cannonball hit right wall at x=%.2f\n", it->x);
            }
            
            // check bottom wall collision (y boundary)
            if (it->y - radius <= bottomWall) 
            {
                it->y = bottomWall + radius;       // push back to just touching the wall
                it->vy = -it->vy * 0.85f;           // reverse y direction with energy loss
                bounced = true;
                printf("cannonball hit bottom wall at y=%.2f\n", it->y);
            } 
            // check top wall collision
            else if (it->y + radius >= topWall) 
            {
                it->y = topWall - radius;          // push back to just touching the wall
                it->vy = -it->vy * 0.85f;           // reverse y direction with energy loss
                bounced = true;
                printf("cannonball hit top wall at y=%.2f\n", it->y);
            }
            
            // if a bounce occurred, apply additional damping
            if (bounced) 
            {
                printf("cannonball bounced at (%.2f, %.2f) with velocity (%.2f, %.2f)\n", 
                       it->x, it->y, it->vx, it->vy);
                // small additional energy loss for realism
                it->vx *= 0.9f;
                it->vy *= 0.9f;
            }
            
            // check if hit the ground
            if (it->y <= groundY) 
            {
                it->y = groundY;
                it->active = false;
                
                // remove the corresponding object from the objects vector
                if (it->objectIndex < objects.size()) 
                {
                    // move to end and pop
                    if (it->objectIndex != objects.size() - 1) 
                    {
                        std::swap(objects[it->objectIndex], objects.back());
                        // update the index of the cannonball that was swapped
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

                printf("cannon ball hit the ground and was removed\n");
                
                // remove from cannonballs vector
                it = cannonBalls.erase(it);
                continue;
            }
            
            // update the corresponding object's position
            if (it->objectIndex < objects.size()) 
            {
                objects[it->objectIndex]->setPosition(it->x, it->y, 0.0f);
            }

            ++it;
        } 
        else 
        {
            // remove inactive cannonballs
            it = cannonBalls.erase(it);
        }
    }
}
