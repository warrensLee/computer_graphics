/******************************************************************************************
 *  File Name:      color.h
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

#pragma once

#include "../core/types.h"
#include "../core/config.h"
#include "../core/math.h"

class TerrainColor
{
    public:
    // constructor
        TerrainColor() = default;
    // predefined terrain colors
        Color lightGreen = {0.52f, 0.72f, 0.32f};
        Color darkGreen = {0.34f, 0.56f, 0.20f};
        Color lightBrown = {0.18f, 0.38f, 0.12f};
        Color darkBrown = {0.45f, 0.32f, 0.18f};
        Color stoneGray = {0.50f, 0.50f, 0.50f};
        Color blackStone = {0.25f, 0.25f, 0.25f};
        Color snowWhite = {0.96f, 0.97f, 0.98f};

    // desert theme
        Color lightSand    = { 0.93f, 0.86f, 0.67f};
        Color goldSand     = {0.85f, 0.74f, 0.45f};
        Color lightTan     = {0.76f, 0.60f, 0.38f};
        Color desertBrown  = {0.60f, 0.42f, 0.25f};
        Color rockBrown    = {0.42f, 0.30f, 0.20f};
        Color darkStone    = {0.25f, 0.20f, 0.18f};
        Color sunPeak      = {0.95f, 0.90f, 0.80f};

// returns height for a given height
        Color getColorAt(float a);      

    private:

};