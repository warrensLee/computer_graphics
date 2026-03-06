/******************************************************************************************
 *  File Name:      controller.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  February 26, 2026
 *
 *  Description:
 *  Defintion of commonly used math tools such as clamping, length, minimum, etc.
 * 
 *  Dependencies:
 *
 *  Notes:
 *
 ******************************************************************************************/

#include "controller.h"

// constructor

// getters
bool Controller::getZoomInPressed() const
{
    return zoomInPressed;
}

bool Controller::getZoomOutPressed() const
{
    return zoomOutPressed;
}

float Controller::getCurrentZoom() const
{
    return currentZoom;
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

float Controller::getCameraX() const
{   
    return xCameraPosition;
}

float Controller::getCameraY() const
{
    return yCameraPosition;
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

void Controller::setCameraX(float x) 
{   
    xCameraPosition = x;
}

void Controller::setCameraY(float y) 
{
    yCameraPosition = y;
}


// functionality
void Controller::handleKeyDown(unsigned char key)
{
     // implementing a zoom bound of 0.0 to  5.0
    switch(key)
    {
    // zoom
        case 'e':
            currentZoom += zoomIncrement;
            break;

        case 'q':
            currentZoom -= zoomIncrement;
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
    if (currentZoom > 5.0f)
    {
        currentZoom = 5.0f;
    }
    if (currentZoom < 0.0f)
    {
        currentZoom = 0.0f;
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
        yCameraPosition -= cameraMoveSpeed;
    if (downPressed)
        yCameraPosition += cameraMoveSpeed;
    if (leftPressed)
        xCameraPosition += cameraMoveSpeed;
    if (rightPressed)
        xCameraPosition -= cameraMoveSpeed;
}

