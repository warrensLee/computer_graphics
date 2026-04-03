/******************************************************************************************
 *  File Name:      types.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 7, 2026
 *
 *  Description:
 *  Defines shared data structures such as vectors and colors used
 *  throughout terrain generation, lighting, and rendering.
 * 
 *  Dependencies:
 *  None
 * 
 *  Notes:
 *  Used to keep common data types consistent across files.
 *
 ******************************************************************************************/

#pragma once

struct Vec2
{
    float x;
    float y;
};

struct Vec3
{
    float x;
    float y;
    float z;
};

struct Color
{
    float r;
    float g;
    float b;
};

struct DragState {
    bool active;
    Vec2 start;
    Vec2 end;
};