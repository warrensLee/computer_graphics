/******************************************************************************************
 *  File Name:      render.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 22, 2026
 *
 *  Description:
 *  Blits the ray-traced pixel buffer to the OpenGL window using glDrawPixels.
 *
 *  Dependencies:
 *  render.h
 *
 *  Notes:
 *  glDrawPixels reads rows bottom-to-top, so we flip with glPixelZoom so that
 *  image[0] is displayed as the top row.
 *
 ******************************************************************************************/

#include "render.h"

void Render::drawRayTracedImage(const unsigned char* buf, int w, int h)
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // flip vertically so image row 0 appears at the top
    glPixelZoom(1.0f, -1.0f);
    glRasterPos2i(0, h);
    glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE, buf);
    glPixelZoom(1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}
