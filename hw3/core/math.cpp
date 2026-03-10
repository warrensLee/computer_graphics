/******************************************************************************************
 *  File Name:      math.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  February 26, 2026
 *
 *  Description:
 *  Implementation of commonly used math tools such as clamping, length, minimum, etc.
 * 
 *  Dependencies:
 *
 *  Notes:
 *
 ******************************************************************************************/

#include "math.h"


// float Math::dotProduct()
// {

// }

// float Math::crossProduct()
// {

// }

// float Math::normalize()
// {

// }

// float Math::clamp()
// {

// }

// float Math::lerp()
// {

// }


// used for noise calcualtion, code is gotten from 
// stack overflow. Might make a new method...
float Math::getRandomBetween(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    
    return a + r;

}

float Math::dotGridGradient(int ix, int iy, float x, float y)
{
    // for given integer position find a gradient
    Vec2 gradient = randomGradient(ix, iy);

    // now compute distance vector:
    float dx =  x - (float)ix;
    float dy =  y - (float)iy;
   
    // now return the dot prodict of these two vectors and their gradients
    return (dx * gradient.x + dy * gradient.y);

}

// simple perlin noise function based on the below tutorial
// https://www.youtube.com/watch?v=kCIaHqb60Cw
float Math::perlinNoise(float x, float y)
{
    // get grid cell corners after casting them as integers
    // flooring will keep values positive (essential for perlin)
    int x0 = (int)floor(x);
    int y0 = (int)floor(y);

    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // now we need interpolation weights
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // compute and interpolate top corners
    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);

    // compute and interpolate bottom corners
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = interpolate(n0, n1, sx);

    float value = interpolate(ix0, ix1, sy);

    return value;
}

// gotten from link in video!
Vec2 Math::randomGradient(int ix, int iy) 
{
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; 
    unsigned a = ix, b = iy;
    a *= 3284157443;
 
    b ^= a << s | a >> w - s;
    b *= 1911520717;
 
    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    
    // Create the vector from the angle
    Vec2 v;
    v.x = sin(random);
    v.y = cos(random);
 
    return v;
}


float Math::interpolate(float a, float b, float w)
{
    return (b - a) * (3.0f - w * 2.0f) * w * w + a;
}

float Math::octavePerlin(float x, float y, int octaves, float persistence, float lacunarity)
{
    float total = 0.0f;
    float frequency = 1.0f;
    float amplitude = 1.0f;
    float maxValue = 0.0f;

    for (int i = 0; i < octaves; ++i)
    {
        total += perlinNoise(x * frequency, y * frequency) * amplitude;
        maxValue += amplitude;

        amplitude *= persistence;
        frequency *= lacunarity;
    }

    if (maxValue == 0.0f)
    {
        return 0.0f;
    }

    return total / maxValue;
}