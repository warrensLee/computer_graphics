/******************************************************************************************
 *  File Name:      controller.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  implements input handling for keyboard controls and camera interaction.
 * 
 *  Dependencies:
 *  controller.h and linked camera/application systems
 * 
 *  Notes:
 *  used to manage movement, zooming, and user interaction.
 *
 ******************************************************************************************/

#include "controller.h"
#include "../app/app.h"
#include <GLUT/glut.h>

// constructor
Controller::Controller() : camera()
{
    // nothing to initialize here
}

// getters
bool Controller::getUpPressed() const
{
    return upPressed;
}

bool Controller::getDownPressed() const
{
    return downPressed;
}

bool Controller::getLeftPressed() const
{
    return leftPressed;
}

bool Controller::getRightPressed() const
{
    return rightPressed;
}

const Camera& Controller::getCamera() const
{
    return camera;
}



// functionality
void Controller::handleKeyDown(unsigned char key)
{
    // handle zoom and movement keys
    switch(key)
    {
    // zoom in/out
        case 'e':
            camera.setCurrentZoom(camera.getCurrentZoom() + zoomIncrement);
            break;

        case 'q':
            camera.setCurrentZoom(camera.getCurrentZoom() - zoomIncrement);
            break;

    // movement
        case 'w':
            upPressed = true;
            break;
        case 'a':
            leftPressed = true;
            break;
        case 's':
            downPressed = true;
            break;
        case 'd':
            rightPressed = true;
            break;
    }
    
    // clamp zoom to reasonable bounds
    if (camera.getCurrentZoom() > 20.0f)
    {
        camera.setCurrentZoom(20.0f);
    }
    if (camera.getCurrentZoom() < 1.0f)
    {
        camera.setCurrentZoom(1.0f);
    }
}

void Controller::handleKeyUp(unsigned char key)
{
    switch(key)
    {
    // movement
        case 'w':
            upPressed = false;
            break;
        case 'a':
            leftPressed = false;
            break;
        case 's':
            downPressed = false;
            break;
        case 'd':
            rightPressed = false;
            break;
    }
}

void Controller::handleSpecialKeyDown(int key)
{
    switch(key)
    {
    // rotation
        case GLUT_KEY_LEFT:
            rotateLeftPressed = true;
            break;
        case GLUT_KEY_RIGHT:
            rotateRightPressed = true;
            break;
    // look up/down
        case GLUT_KEY_UP:
            lookUpPressed = true;
            break;
        case GLUT_KEY_DOWN:
            lookDownPressed = true;
            break;
    }
}

void Controller::handleSpecialKeyUp(int key)
{
    switch(key)
    {
    // rotation
        case GLUT_KEY_LEFT:
            rotateLeftPressed = false;
            break;
        case GLUT_KEY_RIGHT:
            rotateRightPressed = false;
            break;
    // look up/down
        case GLUT_KEY_UP:
            lookUpPressed = false;
            break;
        case GLUT_KEY_DOWN:
            lookDownPressed = false;
            break;
    }
}

void Controller::update()
{
    // handle camera movement
    if (upPressed)
        camera.setCameraY(camera.getCameraY() - cameraMoveSpeed);
    if (downPressed)
        camera.setCameraY(camera.getCameraY() + cameraMoveSpeed);
    if (leftPressed)
        camera.setCameraX(camera.getCameraX() + cameraMoveSpeed);
    if (rightPressed)
        camera.setCameraX(camera.getCameraX() - cameraMoveSpeed);
    
    // handle camera rotation (yaw)
    if (rotateLeftPressed)
        camera.rotateYaw(rotationSpeed);
    if (rotateRightPressed)
        camera.rotateYaw(-rotationSpeed);
    
    // handle looking up/down (pitch)
    if (lookUpPressed)
        camera.rotatePitch(rotationSpeed);
    if (lookDownPressed)
        camera.rotatePitch(-rotationSpeed);
}

void Controller::mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            // start dragging
            isDragging = true;
            startX = x;
            startY = y;
        }
        else if (state == GLUT_UP)
        {
            // end dragging and launch cannon ball
            isDragging = false;
            endX = x;
            endY = y;

            // compute drag vector
            float dx = endX - startX;
            float dy = endY - startY;

            float distance = sqrt(dx * dx + dy * dy);
            
            // avoid division by zero
            if (distance == 0.0f)
                return;

            // normalize direction
            float dirX = dx / distance;
            float dirY = dy / distance;

            // scale by distance for power
            // note: screen y increases downwards, world y increases upwards
            float powerScale = 0.02f;
            float launchVX = dirX;
            float launchVY = -dirY;  // invert y for world coordinates

            // apply power scaling
            launchVX *= distance * powerScale;
            launchVY *= distance * powerScale;

            // clamp speed to maximum
            float speed = sqrt(launchVX * launchVX + launchVY * launchVY);
            if (speed > maxSpeed) {
                launchVX = launchVX / speed * maxSpeed;
                launchVY = launchVY / speed * maxSpeed;
            }

            // launch the cannon ball
            printf("Launching: distance=%f, vx=%f, vy=%f\n", distance, launchVX, launchVY);
            App::callLaunchProjectile(launchVX, launchVY, distance);
        }
    }
}

void Controller::mouseMotion(int x, int y)
{
    if (isDragging)
    {
        endX = x;
        endY = y;

        // You can visualize drag line here
        glutPostRedisplay();
    }
}
        

