/******************************************************************************************
 *  File Name:      render.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Defines the fucntions necessary to terrain as either a filled surface or wireframe. 
 *  Also includes helper methods for vector math used to calculate surface normals for lighting.
 * 
 *  Dependencies:
 *  gl.h, glut.h height.h, terrainColor.h, lighting.h
 * 
 *  Notes:
 *  Filled terrain uses height-based colors and diffuse lighting.
 *
 ******************************************************************************************/

 #pragma once

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "../terrain/height.h"
#include "../terrain/terrainColor.h"
#include "../terrain/lighting.h"

class Render
{
    public:
        Render(Height & height);

        void drawWireframe(const Height& h);
        void drawSurface(const Height& h);

    private:
        Height& h;
        TerrainColor terrainColor;
        Lighting lighting;
        
        static Vec3 subtractVec3(const Vec3& a, const Vec3& b);
        static Vec3 makeVec3(float x, float y, float z);
        static Vec3 getSurfaceNormal(const std::vector<float>& X, const std::vector<float>& Y, const std::vector<float>& Z, int a, int b, int c);
};