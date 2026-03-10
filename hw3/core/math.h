/******************************************************************************************
 *  File Name:      math.h
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

#include <random>
#include "types.h"


class Math
{
    public:
        static float getRandomBetween(float a, float b);
        static float perlinNoise(float x, float y);
        static float octavePerlin(float x, float y, int octaves, float persistence, float lacunarity);


    private:
        static float randomValue(int x, int z);
        static float interpolate(float a, float b, float w);
        static float dotGridGradient(int ix, int iy, float x, float y);
        static Vec2 randomGradient(int ix, int iy);


};

