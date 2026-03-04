/******************************************************************************************
 *  File Name:      config.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  February 26, 2026
 *
 *  Description:
 *  This will hold all configurable data like the gridsize.
 * 
 *  Dependencies:
 *
 *  Notes:
 *  pragama once will make sure this file is ran one, and constexpr will ensure that these values are stored
 *  & calculated on compilation (for optimization).
 *
 ******************************************************************************************/
#pragma once

namespace Config
{
    constexpr inline int GRID_ROWS = 50;
    constexpr inline int GRID_COLS = 50;
    constexpr inline float GRID_SPACE = 0.05f;

    constexpr inline float HEIGHT_SCALE = 0.01f;
    constexpr inline float ROTATION_STEP = 0.07f;
}
