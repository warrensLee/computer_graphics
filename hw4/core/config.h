/******************************************************************************************
 *  File Name:      config.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 3, 2026
 *
 *  Description:
 *  Stores global project constants such as configuration values, camera settings,
 *  and cannonball parameters.
 * 
 *  Dependencies:
 *
 *  Notes:
 *  Used for shared values across multiple files and directories.
 *  Pragama once will make sure this file is ran one, and constexpr will ensure that these values are stored
 *  & calculated on compilation (for optimization).
 *
 ******************************************************************************************/

#pragma once

namespace Config
{
    // camera starting position
    constexpr inline float CAMERA_START_X = 0.0f;
    constexpr inline float CAMERA_START_Y = 4.0f;
    constexpr inline float CAMERA_START_Z = 10.0f;
    
    // camera rotation
    constexpr inline float CAMERA_START_YAW = 0.0f;
    constexpr inline float CAMERA_START_PITCH = 0.0f;
    constexpr inline float CAMERA_START_ROLL = 0.5f;
    
    // camera movement
    constexpr inline float CAMERA_MOVE_SPEED = 0.25f;
    constexpr inline float CAMERA_ZOOM_INCREMENT = 0.2f;
    constexpr inline float CAMERA_ROTATION_SPEED = 1.0f;
    
    // zoom bounds
    constexpr inline float CAMERA_ZOOM_MIN = 2.0f;
    constexpr inline float CAMERA_ZOOM_MAX = 20.0f;
    constexpr inline float CAMERA_ZOOM_START = 9.0f;
    
    // ground settings
    constexpr inline float GROUND_SIZE = 50.0f;
    constexpr inline float GROUND_Z_POSITION = 0.0f;
    
    // cannonball launch parameters
    constexpr inline float CANNONBALL_POWER_SCALE = 0.03f;
    constexpr inline float CANNONBALL_UPWARD_BIAS = 1.0f;
    constexpr inline float CANNONBALL_MAX_SPEED = 10.0f;
    
    // cannonball size
    constexpr inline float CANNONBALL_WIDTH = 2.0f;
    constexpr inline float CANNONBALL_HEIGHT = 2.0f;
    constexpr inline float CANNONBALL_DEPTH = 2.0f;

    // Maximum number of cannonballs that can be active at once
    constexpr inline int MAX_ACTIVE_CANNONBALLS = 3;
}

