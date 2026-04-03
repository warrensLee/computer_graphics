/******************************************************************************************
 *  File Name:      camera.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Implements camera positioning, movement, zooming, and viewing transforms.
 * 
 *  Dependencies:
 *  camera.h
 * 
 *  Notes:
 *  Controls how the terrain scene is viewed.
 *
 ******************************************************************************************/

#include "camera.h"

Camera::Camera() : currentZoom(10.0f), xCameraPosition(0.0f), yCameraPosition(0.0f)
{
}

float Camera::getCameraX() const
{   
    return xCameraPosition;
}

float Camera::getCameraY() const
{
    return yCameraPosition;
}

float Camera::getCurrentZoom() const
{
    return currentZoom;
}
void Camera::setCameraX(float x) 
{   
    xCameraPosition = x;
}

void Camera::setCameraY(float y) 
{
    yCameraPosition = y;
}


void Camera::setCurrentZoom(float z) 
{
    currentZoom = z;
}





