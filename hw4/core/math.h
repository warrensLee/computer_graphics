/******************************************************************************************
 *  File Name:      math.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 7, 2026
 *
 *  Description:
 *  Declares common math functions used throughout the project,
 *  including vector operations and procedural noise tools.
 * 
 *  Dependencies:
 *  types.h, <random>
 * 
 *  Notes:
 *  Central utility file for reusable mathematical operations.
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
        static Vec3 normalize(const Vec3& v);
        static float dotProduct(const Vec3& a, const Vec3& b);
        static Vec3 crossProduct(const Vec3& a, const Vec3& b);


    private:
    // terrain generation
        static float randomValue(int x, int z);
        static float interpolate(float a, float b, float w);
        static float dotGridGradient(int ix, int iy, float x, float y);
        static Vec2 randomGradient(int ix, int iy);

    // lighting functionality 
        static float length(const Vec3& v);


};

