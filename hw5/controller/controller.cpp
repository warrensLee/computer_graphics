/******************************************************************************************
 *  File Name:      controller.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 3, 2026
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

bool Controller::getIsDragging() const 
{ 
    return isDragging; 
}

float Controller::getDragStartX() const 
{ 
    return startX; 
}

float Controller::getDragStartY() const 
{ 
    return startY; 
}

float Controller::getDragEndX() const 
{ 
    return endX; 
}

float Controller::getDragEndY() const 
{ 
    return endY; 
}

// functionality
void Controller::handleKeyDown(unsigned char key)
{
    // // handle zoom and movement keys
    // switch(key)
    // {
    // // zoom in/out
    //     case 'e':
    //         camera.setCurrentZoom(camera.getCurrentZoom() + Config::CAMERA_ZOOM_INCREMENT);
    //         break;

    //     case 'q':
    //         camera.setCurrentZoom(camera.getCurrentZoom() - Config::CAMERA_ZOOM_INCREMENT);
    //         break;

    // // movement
    //     case 'w':
    //         upPressed = true;
    //         break;
    //     case 'a':
    //         leftPressed = true;
    //         break;
    //     case 's':
    //         downPressed = true;
    //         break;
    //     case 'd':
    //         rightPressed = true;
    //         break;
    // }
    
    // // clamp zoom to reasonable bounds
    // if (camera.getCurrentZoom() > Config::CAMERA_ZOOM_MAX)
    // {
    //     camera.setCurrentZoom(Config::CAMERA_ZOOM_MAX);
    // }
    // if (camera.getCurrentZoom() < Config::CAMERA_ZOOM_MIN)  // minimum zoom (more zoomed in)
    // {
    //     camera.setCurrentZoom(Config::CAMERA_ZOOM_MIN);
    // }
}

void Controller::handleKeyUp(unsigned char key)
{
    // switch(key)
    // {
    // // movement
    //     case 'w':
    //         upPressed = false;
    //         break;
    //     case 'a':
    //         leftPressed = false;
    //         break;
    //     case 's':
    //         downPressed = false;
    //         break;
    //     case 'd':
    //         rightPressed = false;
    //         break;
    // }
}


void Controller::update()
{

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
            float powerScale = Config::BASKETBALL_POWER_SCALE;  // reasonable power scale
            float launchVX = dirX;
            float launchVY = -dirY;  // invert y for world coordinates

            // apply power scaling
            launchVX *= distance * powerScale;
            launchVY *= distance * powerScale;
            
            // Add some upward bias to make the cannon ball go in an arc
            launchVY += Config::BASKETBALL_UPWARD_BIAS;  // give it some initial upward velocity

            // clamp speed to maximum
            float speed = sqrt(launchVX * launchVX + launchVY * launchVY);

            if (speed > Config::BASKETBALL_MAX_SPEED) {
                launchVX = launchVX / speed * Config::BASKETBALL_MAX_SPEED;
                launchVY = launchVY / speed * Config::BASKETBALL_MAX_SPEED;
            }

            // Convert click position to world coordinates on the ground plane (z=0)
            int width = glutGet(GLUT_WINDOW_WIDTH);
            int height = glutGet(GLUT_WINDOW_HEIGHT);
            
            if (width == 0) 
                width = 800;
            if (height == 0) 
                height = 600;
            
            // map screen coordinates to world coordinates
            float zoom = camera.getCurrentZoom();
            float aspect = (float)width / (float)height;
            float right = zoom * aspect;
            float left = -right;
            float top = zoom;
            float bottom = -top;
            
            // convert screen (0 to width - 1) to world (left to right)
            float worldX = left + (right - left) * ((float)startX / (float)width);

            // convert screen (0 to height - 1) to world (bottom to top)
            float worldY = bottom + (top - bottom) * ((float)(height - startY) / (float)height);

            worldX += camera.getCameraX();
            worldY += camera.getCameraY();
            
            // the ground is at z = 0, so the ball should be 
            // launched from (worldX, worldY, 0)

            // debugging
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

        // Request redisplay to update the trajectory line
        glutPostRedisplay();
    }
}

void Controller::getDragWorldCoordinates(float& worldStartX, float& worldStartY, float& worldEndX, float& worldEndY) const
{
    // if not dragging, return last known coordinates (or zeros)
    if (!isDragging) 
    {
        worldStartX = worldStartY = worldEndX = worldEndY = 0.0f;
        return;
    }

    // get screen size
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    // map screen coordinates to world coordinates 
    // using the same logic as in mouseButton
    float zoom = camera.getCurrentZoom();
    float aspect = (float)width / (float)height;
    float right = zoom * aspect;
    float left = -right;
    float top = zoom;
    float bottom = -top;
    
    // convert start screen coordinates to world coordinates
    worldStartX = left + (right - left) * ((float)startX / (float)width);
    worldStartY = bottom + (top - bottom) * ((float)(height - startY) / (float)height);
    
    // convert end screen coordinates to world coordinates
    worldEndX = left + (right - left) * ((float)endX / (float)width);
    worldEndY = bottom + (top - bottom) * ((float)(height - endY) / (float)height);
    
    // adjust for camera position
    worldStartX += camera.getCameraX();
    worldStartY += camera.getCameraY();
    worldEndX += camera.getCameraX();
    worldEndY += camera.getCameraY();
}
        

