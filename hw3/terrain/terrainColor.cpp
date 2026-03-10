/******************************************************************************************
 *  File Name:      terrainColor.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 9, 2026
 *
 *  Description:
 *  Implements terrain color selection based on normalized height values.
 * 
 *  Dependencies:
 *  terrainColor.h
 * 
 *  Notes:
 *  Maps terrain height ranges to color bands such as grass, rock, and snow.
 *
 ******************************************************************************************/

#include "terrainColor.h"

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
        return snowTop;
    }
    else // gonna go with random for now
    {
        return snowTop;
    }

}


Color TerrainColor::getDesertColor(float a)      // returns color for a given height
{
    if (a < Config::low1)
    {
        return lightSand;
    }
    else if (a < Config::low2)
    {
        return goldSand;
    }
    else if (a < Config::mid1)
    {
        return lightTan;
    }
    else if (a < Config::mid2)
    {
        return desertBrown;
    }
    else if (a < Config::high1)
    {
        return rockBrown;
    }
    else if (a < Config::high2)
    {
        return darkStone;
    }
    else if (a < Config::top)
    {
        return sunPeak;
    }
    else // gonna go with random for now
    {
        return sunPeak;
    }
}

Color TerrainColor::getVolcanicColor(float a)      // returns color for a given height
{
    if (a < Config::low1)
    {
        return darkLavaRock;
    }
    else if (a < Config::low2)
    {
        return emberBrown;
    }
    else if (a < Config::mid1)
    {
        return ashGray;
    }
    else if (a < Config::mid2)
    {
        return charcoal;
    }
    else if (a < Config::high1)
    {
        return lavaRed;
    }
    else if (a < Config::high2)
    {
        return blackStone2;
    }
    else if (a < Config::top)
    {
        return ashPeak;
    }
    else // gonna go with random for now
    {
        return ashPeak;
    }
}

Color TerrainColor::getAlpineColor(float a)      // returns color for a given height
{
    if (a < Config::low1)
    {
        return pineGreen;
    }
    else if (a < Config::low2)
    {
        return coldGrass;
    }
    else if (a < Config::mid1)
    {
        return coldBrown;
    }
    else if (a < Config::mid2)
    {
        return stoneGray2;
    }
    else if (a < Config::high1)
    {
        return deepStone;
    }
    else if (a < Config::high2)
    {
        return iceShadow;
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

Color TerrainColor::getFantasyColor(float a)      // returns color for a given height
{
    if (a < Config::low1)
    {
        return emerald;
    }
    else if (a < Config::low2)
    {
        return magicGreen;
    }
    else if (a < Config::mid1)
    {
        return violetBrown;
    }
    else if (a < Config::mid2)
    {
        return purpleRock;
    }
    else if (a < Config::high1)
    {
        return shadowStone;
    }
    else if (a < Config::high2)
    {
        return nightPeak;
    }
    else if (a < Config::top)
    {
        return moonSnow;
    }
    else // gonna go with random for now
    {
        return moonSnow;
    }
}