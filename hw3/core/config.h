/******************************************************************************************
 *  File Name:      config.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 7, 2026
 *
 *  Description:
 *  Stores global project constants such as terrain dimensions,
 *  grid spacing, and rendering configuration values.
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

}

