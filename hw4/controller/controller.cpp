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
#include "../core/config.h"
#include <GLUT/glut.h>

// constructor
Controller::Controller() : 
    camera(),
    cameraMoveSpeed(Config::CAMERA_MOVE_SPEED),
    zoomIncrement(Config::CAMERA_ZOOM_INCREMENT),
    rotationSpeed(Config::CAMERA_ROTATION_SPEED),
    maxSpeed(Config::CANNONBALL_MAX_SPEED)
{
    // nothing else to initialize here
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
    if (camera.getCurrentZoom() > Config::CAMERA_ZOOM_MAX)
    {
        camera.setCurrentZoom(Config::CAMERA_ZOOM_MAX);
    }
    if (camera.getCurrentZoom() < Config::CAMERA_ZOOM_MIN)  // minimum zoom (more zoomed in)
    {
        camera.setCurrentZoom(Config::CAMERA_ZOOM_MIN);
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


void Controller::update()
{
    // handle camera movement - intuitive controls
    // W: move camera up (scene moves down) - press W to see more above
    // S: move camera down (scene moves up) - press S to see more below
    // A: move camera left (scene moves right) - press A to see more to the left
    // D: move camera right (scene moves left) - press D to see more to the right
    // if (upPressed)
    //     camera.setCameraY(camera.getCameraY() + cameraMoveSpeed);  // W: move camera up
    // if (downPressed)
    //     camera.setCameraY(camera.getCameraY() - cameraMoveSpeed);  // S: move camera down
    if (leftPressed)
        camera.setCameraX(camera.getCameraX() - cameraMoveSpeed);  // A: move camera left
    if (rightPressed)
        camera.setCameraX(camera.getCameraX() + cameraMoveSpeed);  // D: move camera right
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
            float powerScale = Config::CANNONBALL_POWER_SCALE;  // reasonable power scale
            float launchVX = dirX;
            float launchVY = -dirY;  // invert y for world coordinates

            // apply power scaling
            launchVX *= distance * powerScale;
            launchVY *= distance * powerScale;
            
            // Add some upward bias to make the cannon ball go in an arc
            launchVY += Config::CANNONBALL_UPWARD_BIAS;  // give it some initial upward velocity

            // clamp speed to maximum
            float speed = sqrt(launchVX * launchVX + launchVY * launchVY);
            if (speed > maxSpeed) {
                launchVX = launchVX / speed * maxSpeed;
                launchVY = launchVY / speed * maxSpeed;
            }

            // Convert click position to world coordinates on the ground plane (z=0)
            int width = glutGet(GLUT_WINDOW_WIDTH);
            int height = glutGet(GLUT_WINDOW_HEIGHT);
            
            if (width == 0) 
                width = 800;
            if (height == 0) 
                height = 600;
            
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
            
            // Adjust for camera position (scene is translated opposite to camera)
            // In app.cpp: glTranslatef(-cameraX, -cameraY, -cameraZ)
            // So we need to add camera position to get correct world position
            worldX += camera.getCameraX();
            worldY += camera.getCameraY();
            
            // The ground is at z=0, so the cannonball should be launched from (worldX, worldY, 0)
            // But launchProjectile expects x and y coordinates, which match worldX and worldY
            printf("Mouse click at screen (%d, %d) -> world (%f, %f, 0.0)\n", startX, startY, worldX, worldY);
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
        

