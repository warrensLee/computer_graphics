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

Camera::Camera() : currentZoom(10.0f), xCameraPosition(0.0f), yCameraPosition(5.0f), zCameraPosition(20.0f),
                   yaw(0.0f), pitch(0.0f), roll(0.0f)
{
    // Starting camera position:
    // x: 0.0f (left/right)
    // y: 5.0f (up/down) - higher to see more
    // z: 20.0f (forward/back - positive means camera is in front of scene)
    // zoom: 10.0f (smaller = more zoomed in)
    // To change starting position, modify the values above and in camera.h
}

float Camera::getCameraX() const
{   
    return xCameraPosition;
}

float Camera::getCameraY() const
{
    return yCameraPosition;
}

float Camera::getCameraZ() const
{
    return zCameraPosition;
}

float Camera::getCurrentZoom() const
{
    return currentZoom;
}

float Camera::getYaw() const
{
    return yaw;
}

float Camera::getPitch() const
{
    return pitch;
}

float Camera::getRoll() const
{
    return roll;
}

void Camera::setCameraX(float x) 
{   
    xCameraPosition = x;
}

void Camera::setCameraY(float y) 
{
    yCameraPosition = y;
}

void Camera::setCameraZ(float z) 
{
    zCameraPosition = z;
}

void Camera::setCurrentZoom(float z) 
{
    currentZoom = z;
}

void Camera::setYaw(float yaw_)
{
    yaw = yaw_;
}

void Camera::setPitch(float pitch_)
{
    pitch = pitch_;
}

void Camera::setRoll(float roll_)
{
    roll = roll_;
}

void Camera::rotateYaw(float delta)
{
    yaw += delta;
}

void Camera::rotatePitch(float delta)
{
    pitch += delta;
}

void Camera::rotateRoll(float delta)
{
    roll += delta;
}





