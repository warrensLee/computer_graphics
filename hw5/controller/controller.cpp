/******************************************************************************************
 *  File Name:      controller.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 22, 2026
 *
 *  Description:
 *  Implements keyboard input handling and dt-based camera movement.
 *
 *  Dependencies:
 *  controller.h
 *
 *  Notes:
 *  Q/E zooms the camera.
 *
 ******************************************************************************************/

#include "controller.h"

Controller::Controller() : camera() {}

const Camera& Controller::getCamera() const
{
    return camera;
}

void Controller::handleKeyDown(unsigned char key)
{
    switch(key)
    {
        case 'w': upPressed = true;  
            break;
        case 'a': leftPressed = true;  
            break;
        case 's': downPressed = true;  
            break;
        case 'd': rightPressed = true;  
            break;
    }
}

void Controller::handleKeyUp(unsigned char key)
{
    switch(key)
    {
        case 'w': upPressed = false; 
            break;
        case 'a': leftPressed = false; 
            break;
        case 's': downPressed = false; 
            break;
        case 'd': rightPressed = false; 
            break;
    }
}

void Controller::update(float dt)
{
    const float speed = 3.0f;   // units per second
    float delta = speed * dt;

    if (upPressed)    
        camera.setCameraY(camera.getCameraY() + delta);
    if (downPressed)  
        camera.setCameraY(camera.getCameraY() - delta);
    if (leftPressed)  
        camera.setCameraX(camera.getCameraX() - delta);
    if (rightPressed) 
        camera.setCameraX(camera.getCameraX() + delta);
}
