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

#include "texture.h"

//---------------------------------------
// Initialize texture image
//---------------------------------------
void Texture::init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
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