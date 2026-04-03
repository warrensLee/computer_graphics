/******************************************************************************************
 *  File Name:      texture.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  April 2, 2026
 *
 *  Description:
 *  Declares texture loading functionality.
 * 
 *  Dependencies:
 *  OpenGL, GLUT, im_color
 * 
 *  Notes:
 *  Used by rendering system.
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

        static void init_texture(const char *name, unsigned char *&texture, int &xdim, int &ydim);

};
