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


float Math::dotProduct()
{

}

float Math::crossProduct()
{

}

float Math::normalize()
{

}

float Math::clamp()
{

}

float Math::lerp()
{

}

float Math::getRandomBetween(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    
    return a + r;

}