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
#include "../core/config.h"

Camera::Camera() : 
    currentZoom(Config::CAMERA_ZOOM_START), 
    xCameraPosition(Config::CAMERA_START_X), 
    yCameraPosition(Config::CAMERA_START_Y), 
    zCameraPosition(Config::CAMERA_START_Z),
    yaw(Config::CAMERA_START_YAW), 
    pitch(Config::CAMERA_START_PITCH), 
    roll(Config::CAMERA_START_ROLL)
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





