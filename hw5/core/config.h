/******************************************************************************************
 *  File Name:      config.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 22, 2026
 *
 *  Description:
 *  Global constants for the ray tracer: window size, camera defaults.
 *
 *  Dependencies:
 *  none
 *
 *  Notes:
 *  constexpr ensures values are resolved at compile time.
 *
 ******************************************************************************************/

#pragma once

namespace Config
{
    // window size
    constexpr inline int XDIM = 400;
    constexpr inline int YDIM = 400;

    // camera starting position (used by Controller / Camera)
    constexpr inline float CAMERA_START_X = 0.0f;
    constexpr inline float CAMERA_START_Y = 0.0f;
    constexpr inline float CAMERA_START_Z = 0.0f;

    // camera rotation defaults
    constexpr inline float CAMERA_START_YAW   = 0.0f;
    constexpr inline float CAMERA_START_PITCH = 0.0f;
    constexpr inline float CAMERA_START_ROLL  = 0.0f;

    // camera movement
    constexpr inline float CAMERA_MOVE_SPEED     = 0.25f;
    constexpr inline float CAMERA_ZOOM_INCREMENT = 0.2f;
    constexpr inline float CAMERA_ROTATION_SPEED = 1.0f;

    // zoom bounds (kept for Camera class)
    constexpr inline float CAMERA_ZOOM_MIN   = 2.0f;
    constexpr inline float CAMERA_ZOOM_MAX   = 20.0f;
    constexpr inline float CAMERA_ZOOM_START = 9.0f;
}
