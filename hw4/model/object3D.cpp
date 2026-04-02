/******************************************************************************************
 *  File Name:      object3D.cpp
 *  Author:         Warren Roberts
 *  Created:        March 25, 2026
 *  Last Modified:  March 28, 2026
 *
 *  Description:
 * 
 *  Dependencies:
 *  none
 * 
 *  Notes:
 *
 ******************************************************************************************/

#include "object3D.h"
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cmath>


void Object3D::block(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax)
{
   // Define 8 vertices
   float ax = xmin, ay = ymin, az = zmax;
   float bx = xmax, by = ymin, bz = zmax;
   float cx = xmax, cy = ymax, cz = zmax;
   float dx = xmin, dy = ymax, dz = zmax;

   float ex = xmin, ey = ymin, ez = zmin;
   float fx = xmax, fy = ymin, fz = zmin;
   float gx = xmax, gy = ymax, gz = zmin;
   float hx = xmin, hy = ymax, hz = zmin;

   // Draw 6 faces
   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(bx, by, bz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(cx, cy, cz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(dx, dy, dz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(hx, hy, hz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(gx, gy, gz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(bx, by, bz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(cx, cy, cz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 3.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(2.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(2.0, 2.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(0.0, 2.0);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 3.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(3.0, 0.0);
   glVertex3f(cx, cy, cz);
   glTexCoord2f(3.0, 3.0);
   glVertex3f(dx, dy, dz);
   glTexCoord2f(0.0, 3.0);
   glVertex3f(hx, hy, hz);
   glEnd();
}

//---------------------------------------
// Initialize sphere surface and normals
//---------------------------------------
void Object3D::sphere(Surface &s)
{
   // Initialize sphere surface and normals
   for (int u = 0; u < SIZE; u++)
   {
      float angle1 = 2 * u * M_PI / (SIZE - 1);
      for (int v = 0; v < SIZE; v++)
      {
         float angle2 = v * M_PI / (SIZE - 1);
         s.Px[u][v] = s.Nx[u][v] = sin(angle2) * cos(angle1);
         s.Py[u][v] = s.Ny[u][v] = sin(angle2) * sin(angle1);
         s.Pz[u][v] = s.Nz[u][v] = cos(angle2);
      }
   }
}

//---------------------------------------
// Draw sphere using triangle strips
//---------------------------------------
void Object3D::drawSphere(const Surface& s)
{
   for (int u = 0; u < SIZE - 1; u++)
   {
      glBegin(GL_TRIANGLE_STRIP);
      for (int v = 0; v < SIZE; v++)
      {
         // Calculate texture coordinates
         float texU = (float)u / (SIZE - 1);
         float texV = (float)v / (SIZE - 1);
         
         // First point
         glTexCoord2f(texU, texV);
         glNormal3f(s.Nx[u][v], s.Ny[u][v], s.Nz[u][v]);
         glVertex3f(s.Px[u][v], s.Py[u][v], s.Pz[u][v]);
         
         // Second point
         glTexCoord2f((float)(u + 1) / (SIZE - 1), texV);
         glNormal3f(s.Nx[u + 1][v], s.Ny[u + 1][v], s.Nz[u + 1][v]);
         glVertex3f(s.Px[u + 1][v], s.Py[u + 1][v], s.Pz[u + 1][v]);
      }
      glEnd();
   }
}
int Object3D::getTexture() const
{
   return texture;
}

void Object3D::setTexture(int t)
{
   texture = t;
}

// get / set
float Object3D::getX() const
{
   return x;
}

float Object3D::getY() const
{
   return y;
}

float Object3D::getZ() const
{
   return z;
}

float Object3D::getWidth() const
{
   return width;
}

float Object3D::getHeight() const
{
   return height;
}

float Object3D::getDepth() const
{
   return depth;
}


void Object3D::setPosition(float px, float py, float pz)
{
   x = px;
   y = py;
   z = pz;
}

void Object3D::setSize(float w, float h, float d)
{
   width = w;
   height = h;
   depth = d;
}
