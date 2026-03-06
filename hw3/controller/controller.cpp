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


// setters   
void Controller::setZoomInPressed(bool a)
{
    zoomInPressed = a;
}

void Controller::setZoomOutPressed(bool a)
{
    zoomOutPressed = a;
}


// functionality
void Controller::handleKey(unsigned char key)
{
     // I will do a zoom bound of -5 to  5
    switch(key)
    {
        case 'e':
            currentZoom += zoomIncrement;
            break;

        case 'q':
            currentZoom -= zoomIncrement;
            break;
    }
    if (currentZoom > 5.0f)
    {
        currentZoom = 5.0f;
    }
    if (currentZoom < -5.0f)
    {
        currentZoom = -5.0f;
    }

}

