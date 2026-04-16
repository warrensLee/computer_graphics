/******************************************************************************************
 *  File Name:      camera.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  April 3, 2026
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
#include "../core/config.h"

Camera::Camera()
{
    currentZoom = Config::CAMERA_ZOOM_START;
    xCameraPosition = Config::CAMERA_START_X;
    yCameraPosition = Config::CAMERA_START_Y;
    zCameraPosition = Config::CAMERA_START_Z;
    yaw = Config::CAMERA_START_YAW; 
    pitch= Config::CAMERA_START_PITCH; 
    roll =Config::CAMERA_START_ROLL;
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

void Camera::setYaw(float dYaw)
{
    yaw = dYaw;
}

void Camera::setPitch(float dPitch)
{
    pitch = dPitch;
}

void Camera::setRoll(float dRoll)
{
    roll = dRoll;
}

void Camera::rotateYaw(float d)
{
    yaw += d;
}

void Camera::rotatePitch(float d)
{
    pitch += d;
}

void Camera::rotateRoll(float d)
{
    roll += d;
}





