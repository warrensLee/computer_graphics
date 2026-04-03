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
    // handle camera movement (optional - we can keep this or remove)
    if (upPressed)
        camera.setCameraY(camera.getCameraY() - cameraMoveSpeed);
    if (downPressed)
        camera.setCameraY(camera.getCameraY() + cameraMoveSpeed);
    if (leftPressed)
        camera.setCameraX(camera.getCameraX() + cameraMoveSpeed);
    if (rightPressed)
        camera.setCameraX(camera.getCameraX() - cameraMoveSpeed);
    
    // Disable camera rotation for simplicity
    // (commented out to keep camera fixed)
    /*
    if (rotateLeftPressed)
        camera.rotateYaw(rotationSpeed);
    if (rotateRightPressed)
        camera.rotateYaw(-rotationSpeed);
    
    if (lookUpPressed)
        camera.rotatePitch(rotationSpeed);
    if (lookDownPressed)
        camera.rotatePitch(-rotationSpeed);
    */
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
            // Store click position for spawning cannon ball
            clickWorldX = 0.0f;  // We'll calculate this
            clickWorldY = 0.0f;
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
            float powerScale = 0.02f;  // reasonable power scale
            float launchVX = dirX;
            float launchVY = -dirY;  // invert y for world coordinates

            // apply power scaling
            launchVX *= distance * powerScale;
            launchVY *= distance * powerScale;
            
            // Add some upward bias to make the cannon ball go in an arc
            launchVY += 1.0f;  // give it some initial upward velocity

            // clamp speed to maximum
            float speed = sqrt(launchVX * launchVX + launchVY * launchVY);
            if (speed > maxSpeed) {
                launchVX = launchVX / speed * maxSpeed;
                launchVY = launchVY / speed * maxSpeed;
            }

            // Convert click position to world coordinates
            // Get current window dimensions for accurate mapping
            int width = glutGet(GLUT_WINDOW_WIDTH);
            int height = glutGet(GLUT_WINDOW_HEIGHT);
            
            if (width == 0) width = 800;
            if (height == 0) height = 600;
            
            // Map screen coordinates to world coordinates
            // Using orthographic projection bounds from app.cpp
            float zoom = camera.getCurrentZoom();
            float aspect = (float)width / (float)height;
            float right = zoom * aspect;
            float left = -right;
            float top = zoom;
            float bottom = -top;
            
            // Convert screen (0 to width-1) to world (left to right)
            float worldX = left + (right - left) * ((float)startX / (float)width);
            // Convert screen (0 to height-1) to world (bottom to top) - invert Y
            float worldY = bottom + (top - bottom) * ((float)(height - startY) / (float)height);
            
            // No additional adjustment - the orthographic projection is linear
            
            // launch the cannon ball from click position
            printf("Launching from (%f, %f): distance=%f, vx=%f, vy=%f\n", worldX, worldY, distance, launchVX, launchVY);
            App::callLaunchProjectile(launchVX, launchVY, distance, worldX, worldY);
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
        

