/******************************************************************************************
 *  File Name:      camera.h
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
#include "../core/libim/im_color.h"
#include "../view/render.h"

class Texture
{
    public:
    // constructors
        Texture() = default;

        static void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim);

    private:




};
