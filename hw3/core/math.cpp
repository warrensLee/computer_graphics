/******************************************************************************************
 *  File Name:      math.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 9, 2026
 *
 *  Description:
 *  Implements reusable mathematical utilities such as interpolation,
 *  dot product, cross product, normalization, random values, and Perlin noise.
 * 
 *  Dependencies:
 *  math.h
 * 
 *  Notes:
 *  Provides core support for terrain generation and lighting calculations.
 *
 ******************************************************************************************/


#include "math.h"


// used for noise calcualtion, code is gotten from 
// stack overflow. Might make a new method...
float Math::getRandomBetween(float a, float b)
{
    // this is currently unused, but initially worked
    // as my noise function, that is untill I decided
    // to make real noise that was not like TV static
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
    // i.e blends the top row
    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);

    // compute and interpolate bottom corners
    // i.e blends the bottom row
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

// typical linear interpolation aka lerp
float Math::interpolate(float a, float b, float w)
{
    return (b - a) * (3.0f - w * 2.0f) * w * w + a;
}

// used to compute each octave 
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

// lighting functionality 

float Math::dotProduct(const Vec3& a, const Vec3& b)
{
    // simple dot product calculator
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Math::crossProduct(const Vec3& a, const Vec3& b)
{
    // regilar cross product calculator
    Vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

float Math::length(const Vec3& v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 Math::normalize(const Vec3& v)
{
    // get length of vectors
    float len = length(v);

    // base case of no length
    if (len == 0.0f)
    {
        return {0.0f, 1.0f, 0.0f};
    }

    // now normalize this vector
    Vec3 result;
    result.x = v.x / len;
    result.y = v.y / len;
    result.z = v.z / len;
    return result;
}