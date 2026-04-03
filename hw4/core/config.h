/******************************************************************************************
 *  File Name:      config.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  April 3, 2026
 *
 *  Description:
 *  Stores global project constants such as terrain dimensions,
 *  grid spacing, rendering configuration values, camera settings,
 *  and cannonball parameters.
 * 
 *  Dependencies:
 *
 *  Notes:
 *  Used for shared values across multiple systems.
 *  Pragama once will make sure this file is ran one, and constexpr will ensure that these values are stored
 *  & calculated on compilation (for optimization).
 *
 ******************************************************************************************/

#pragma once

namespace Config
{
    // Terrain settings
    constexpr inline int GRID_ROWS = 100;
    constexpr inline int GRID_COLS = 100;
    constexpr inline float GRID_SPACE = 0.05f;

    constexpr inline float HEIGHT_SCALE = 0.05f;
    constexpr inline float ROTATION_STEP = 0.1f;

    constexpr inline float low1 = 0.15f;
    constexpr inline float low2 = 0.3f;
    constexpr inline float mid1 = 0.45f;
    constexpr inline float mid2 = 0.6f;
    constexpr inline float high1 = 0.75f;
    constexpr inline float high2 = 0.85f;
    constexpr inline float top = 1.0f;

    // Camera starting position
    constexpr inline float CAMERA_START_X = 0.0f;
    constexpr inline float CAMERA_START_Y = 5.0f;
    constexpr inline float CAMERA_START_Z = 20.0f;
    
    // Camera rotation
    constexpr inline float CAMERA_START_YAW = 0.0f;
    constexpr inline float CAMERA_START_PITCH = 0.0f;
    constexpr inline float CAMERA_START_ROLL = 0.5f;
    
    // Camera movement
    constexpr inline float CAMERA_MOVE_SPEED = 0.25f;
    constexpr inline float CAMERA_ZOOM_INCREMENT = 0.2f;
    constexpr inline float CAMERA_ROTATION_SPEED = 1.0f;
    
    // Zoom limits
    constexpr inline float CAMERA_ZOOM_MIN = 2.0f;
    constexpr inline float CAMERA_ZOOM_MAX = 20.0f;
    constexpr inline float CAMERA_ZOOM_START = 10.0f;
    
    // Ground settings
    constexpr inline float GROUND_SIZE = 50.0f;
    constexpr inline float GROUND_Z_POSITION = 0.0f;
    
    // Cannonball launch parameters
    constexpr inline float CANNONBALL_POWER_SCALE = 0.02f;
    constexpr inline float CANNONBALL_UPWARD_BIAS = 1.0f;
    constexpr inline float CANNONBALL_MAX_SPEED = 10.0f;
    
    // Cannonball size
    constexpr inline float CANNONBALL_WIDTH = 1.0f;
    constexpr inline float CANNONBALL_HEIGHT = 1.0f;
    constexpr inline float CANNONBALL_DEPTH = 1.0f;
}

