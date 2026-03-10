/******************************************************************************************
 *  File Name:      color.cpp
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

#include "terrainColor.h"

Color randomColor = {Math::getRandomBetween( 0.0,  1.0), Math::getRandomBetween( 0.0,  1.0), Math::getRandomBetween( 0.0,  1.0)};

Color TerrainColor::getColorAt(float a)      // returns height for a given height
{
    if (a < Config::low1)
    {
        return darkGreen;
    }
    else if (a < Config::low2)
    {
        return lightGreen;
    }
    else if (a < Config::mid1)
    {
        return lightBrown;
    }
    else if (a < Config::mid2)
    {
        return darkBrown;
    }
    else if (a < Config::high1)
    {
        return stoneGray;
    }
    else if (a < Config::high2)
    {
        return blackStone;
    }
    else if (a < Config::top)
    {
        return snowWhite;
    }
    else // gonna go with random for now
    {
        return snowWhite;
    }

}