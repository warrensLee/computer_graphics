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
        Color lightGreen = {0.55f, 0.78f, 0.42f};
        Color darkGreen = {0.13f, 0.42f, 0.18f};
        Color lightBrown = {0.72f, 0.58f, 0.38f};
        Color darkBrown = {0.36f, 0.24f, 0.14f};
        Color stoneGray = {0.50f, 0.50f, 0.50f};
        Color blackStone = {0.18f, 0.18f, 0.18f};
        Color snowWhite = {0.96f, 0.96f, 0.98f};

// returns height for a given height
        Color getColorAt(float a);      

    private:

};