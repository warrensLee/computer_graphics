/******************************************************************************************
 *  File Name:      render.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Renders the terrain as either a filled surface or wireframe. Also includes helper
 *  methods for vector math used to calculate surface normals for lighting.
 * 
 *  Dependencies:
 *  render.h and its dependencies
 * 
 *  Notes:
 *  Surface rendering applies terrain colors and diffuse lighting per triangle.
 *
 ******************************************************************************************/


#include "render.h"

void Render::init()
{
    glEnable(GL_TEXTURE_2D);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    init_texture((char*)"textures/brick.jpg", texture1, xdim1, ydim1);
    init_texture((char*)"textures/gravel.jpg", texture2, xdim2, ydim2);
}

void Render::draw()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    // Draw objects
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim1, ydim1, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1);
    object3D::block(-1, -1, -1, 2, 2, 2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim2, ydim2, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2);
    object3D::block(-2, -2, -2, 1, 1, 1);
}

//---------------------------------------
// Initialize texture image
//---------------------------------------
void Render::init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
{
   // Read jpg image
   im_color image;
   image.ReadJpg(name);
   printf("Reading image %s\n", name);
   xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   image.Interpolate(xdim, ydim);
   printf("Interpolating %dx%d to %dx%d\n", 
      image.R.Xdim, image.R.Ydim, xdim, ydim);

   // Copy image into texture array
   texture = (unsigned char *)malloc((unsigned int)(xdim*ydim*3));
   int index = 0;
   for (int y = 0; y < ydim; y++)
      for (int x = 0; x < xdim; x++)
      {
         texture[index++] = (unsigned char)(image.R.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.G.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.B.Data2D[y][x]);
      }
}

