/******************************************************************************************
 *  File Name:      render.h
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

#include "../terrain/height.h"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "../terrain/height.h"
#include "../core/types.h"
#include "../terrain/terrainColor.h"

class Render
{
    public:
        Height& h;
        TerrainColor terrainColor;

        Render(Height & height);

        void drawWireframe(const Height& h);
        void drawSurface(const Height& h);

    private:

};