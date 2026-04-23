/******************************************************************************************
 *  File Name:      render.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 22, 2026
 *
 *  Description:
 *  Declares the Render class, which blits the ray-traced pixel buffer to the screen.
 *
 *  Dependencies:
 *  OpenGL, GLUT
 *
 *  Notes:
 *  All rendering output is produced by RayTracer; this class only handles display.
 *
 ******************************************************************************************/

#pragma once

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

class Render
{
public:
    Render() = default;
    void drawRayTracedImage(const unsigned char* buf, int w, int h);
};
