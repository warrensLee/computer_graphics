/******************************************************************************************
 *  File Name:      terrainColor.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Declares color lookup methods used to assign terrain colors from height values.
 * 
 *  Dependencies:
 *  types.h, config.h, math.h
 * 
 *  Notes:
 *  Keeps terrain coloring separate from rendering logic. Color themes were AI
 *  generated to save time on harcoded colors.
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

    // returns height for a given height
        Color getColorAt(float a);    

    // //********************** PREDEFINED TERRAIN COLORS **********************//

    // forest theme
        Color lightGreen = {0.52f, 0.72f, 0.32f};
        Color darkGreen = {0.34f, 0.56f, 0.20f};
        Color lightBrown = {0.18f, 0.38f, 0.12f};
        Color darkBrown = {0.45f, 0.32f, 0.18f};
        Color stoneGray = {0.50f, 0.50f, 0.50f};
        Color blackStone = {0.25f, 0.25f, 0.25f};
        Color snowTop = {0.96f, 0.97f, 0.98f};

    // desert theme
        Color lightSand    = { 0.93f, 0.86f, 0.67f};
        Color goldSand     = {0.85f, 0.74f, 0.45f};
        Color lightTan     = {0.76f, 0.60f, 0.38f};
        Color desertBrown  = {0.60f, 0.42f, 0.25f};
        Color rockBrown    = {0.42f, 0.30f, 0.20f};
        Color darkStone    = {0.25f, 0.20f, 0.18f};
        Color sunPeak      = {0.95f, 0.90f, 0.80f};

    // volcanic theme
        Color ashGray      = {0.35f, 0.35f, 0.35f};
        Color charcoal     = {0.25f, 0.25f, 0.25f};
        Color darkLavaRock = {0.18f, 0.12f, 0.10f};
        Color emberBrown   = {0.35f, 0.15f, 0.10f};
        Color lavaRed      = {0.55f, 0.10f, 0.05f};
        Color blackStone2   = {0.08f, 0.08f, 0.08f};
        Color ashPeak      = {0.85f, 0.85f, 0.82f};

    // alpine theme
        Color coldGrass   = {0.60f, 0.75f, 0.55f};
        Color pineGreen   = {0.28f, 0.45f, 0.24f};
        Color coldBrown   = {0.42f, 0.34f, 0.26f};
        Color stoneGray2   = {0.58f, 0.58f, 0.60f};
        Color deepStone   = {0.35f, 0.35f, 0.38f};
        Color iceShadow   = {0.72f, 0.76f, 0.82f};
        Color snowWhite   = {0.98f, 0.99f, 1.00f};
    
    // fantasy theme
        Color magicGreen  = {0.35f, 0.85f, 0.50f};
        Color emerald     = {0.10f, 0.65f, 0.35f};
        Color violetBrown = {0.42f, 0.28f, 0.50f};
        Color purpleRock  = {0.36f, 0.24f, 0.48f};
        Color shadowStone = {0.20f, 0.18f, 0.30f};
        Color nightPeak   = {0.10f, 0.10f, 0.18f};
        Color moonSnow    = {0.88f, 0.92f, 1.00f};

    // methods:
        Color getDesertColor(float a);
        Color getVolcanicColor(float a);
        Color getAlpineColor(float a);
        Color getFantasyColor(float a);
    

    private:

};