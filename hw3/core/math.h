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


class Math
{
    public:
        float dotProduct();
        float crossProduct();
        float normalize();
        float clamp();
        float lerp(); 
        static float getRandomBetween(float a, float b);
};

