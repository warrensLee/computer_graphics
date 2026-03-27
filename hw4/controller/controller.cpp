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

// constructor
Controller::Controller() : camera()
{

}

// getters
bool Controller::getZoomInPressed() const
{
    return zoomInPressed;
}

bool Controller::getZoomOutPressed() const
{
    return zoomOutPressed;
}

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

// setters   
void Controller::setZoomInPressed(bool a)
{
    zoomInPressed = a;
}

void Controller::setZoomOutPressed(bool a)
{
    zoomOutPressed = a;
}

void Controller::setUpPressed(bool a)
{
    upPressed = a;
}

void Controller::setDownPressed(bool a)
{
    downPressed = a;
}

void Controller::setLeftPressed(bool a)
{
    leftPressed = a;
}

void Controller::setRightPressed(bool a)
{
    rightPressed = a;
}

Camera Controller::getCamera() const
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
    }
    // actual clamp logic as mentioned above
    if (camera.getCurrentZoom() > 5.0f)
    {
        camera.setCurrentZoom(5.0f);
    }
    if (camera.getCurrentZoom() < 0.0f)
    {
        camera.setCurrentZoom(0.0f);
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
    if (upPressed)
        camera.setCameraY(camera.getCameraY() - cameraMoveSpeed);
    if (downPressed)
        camera.setCameraY(camera.getCameraY() + cameraMoveSpeed);
    if (leftPressed)
        camera.setCameraX(camera.getCameraX() + cameraMoveSpeed);
    if (rightPressed)
        camera.setCameraX(camera.getCameraX() - cameraMoveSpeed);

}

        

