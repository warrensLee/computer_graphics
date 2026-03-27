/******************************************************************************************
 *  File Name:      3DObject.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Declares camera position and viewing controls for scene navigation.
 * 
 *  Dependencies:
 *  none
 * 
 *  Notes:
 *  Used by rendering and controller systems.
 *
 ******************************************************************************************/
#pragma once

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

class object3D
{
    public:
    // constructors
        object3D() = default;

        static void block(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);

    private:



};
