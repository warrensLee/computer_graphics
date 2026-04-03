/******************************************************************************************
 *  File Name:      controller.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Implements input handling for keyboard controls and camera interaction.
 * 
 *  Dependencies:
 *  controller.h and linked camera/application systems
 * 
 *  Notes:
 *  Used to manage movement, zooming, and user interaction.
 *
 ******************************************************************************************/

#include "controller.h"
#include "../app/app.h"
// constructor
Controller::Controller() : camera()
{

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
     // implementing a zoom bound of 0.0 to  5.0
    switch(key)
    {
    // zoom
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
    // rotation
        case 'z':
            rotateLeftPressed = true;
            break;
        case 'x':
            rotateRightPressed = true;
            break;
    }
    // actual clamp logic as mentioned above
    if (camera.getCurrentZoom() > 20.0f)
    {
        camera.setCurrentZoom(20.0f);
    }
    if (camera.getCurrentZoom() < 0.5f)
    {
        camera.setCurrentZoom(0.5f);
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
    // rotation
        case 'z':
            rotateLeftPressed = false;
            break;
        case 'x':
            rotateRightPressed = false;
            break;
    }
}

void Controller::update()
{
    if (upPressed)
        camera.setCameraY(camera.getCameraY() - cameraMoveSpeed);
    if (downPressed)
        camera.setCameraY(camera.getCameraY() + cameraMoveSpeed);
    if (leftPressed)
        camera.setCameraX(camera.getCameraX() + cameraMoveSpeed);
    if (rightPressed)
        camera.setCameraX(camera.getCameraX() - cameraMoveSpeed);
    
    // Apply rotation
    if (rotateLeftPressed)
        camera.rotateYaw(rotationSpeed);
    if (rotateRightPressed)
        camera.rotateYaw(-rotationSpeed);

}

void Controller::mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            isDragging = true;
            startX = x;
            startY = y;
        }
        else if (state == GLUT_UP)
        {
            isDragging = false;
            endX = x;
            endY = y;

            // Compute shot vector here
            float dx = endX - startX;
            float dy = endY - startY;

            float distance = sqrt(dx * dx + dy * dy);
            
            // safe guard to avoid dividing by 0
            if (distance == 0.0f)
                return;

            // Normalize direction
            float dirX = dx / distance;
            float dirY = dy / distance;

            // Scale by distance for power, and adjust signs for coordinate system
            // In screen coordinates, y increases downwards, but in world coordinates, y should increase upwards
            // So invert dy
            float powerScale = 0.02f;
            float launchVX = dirX;
            float launchVY = -dirY;  // Invert for proper world coordinates

            // Scale by distance (power)
            launchVX *= distance * powerScale;
            launchVY *= distance * powerScale;

            // Clamp maximum speed if needed
            float speed = sqrt(launchVX * launchVX + launchVY * launchVY);

            // make sure its not going crazy fast
            if (speed > maxSpeed) {
                launchVX = launchVX / speed * maxSpeed;
                launchVY = launchVY / speed * maxSpeed;
            }

            // now to launch
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
        

