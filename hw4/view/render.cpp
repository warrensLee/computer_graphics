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

    // Load raw image data
    Texture::init_texture((char*)"textures/brick.jpg", texture1, xdim1, ydim1);
    Texture::init_texture((char*)"textures/gravel.jpg", texture2, xdim2, ydim2);

    // Create 2 OpenGL textures
    glGenTextures(2, texIDs);

    // Texture 0 = brick
    glBindTexture(GL_TEXTURE_2D, texIDs[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim1, ydim1, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1);

    // Texture 1 = gravel
    glBindTexture(GL_TEXTURE_2D, texIDs[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim2, ydim2, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2);
}

void Render::drawObject(const Object3D& obj)
{
    int tex = obj.getTexture();
    if (tex < 0 || tex > 1)
        tex = 0;

    glBindTexture(GL_TEXTURE_2D, texIDs[tex]);

    glPushMatrix();

    glTranslatef(obj.getX(), obj.getY(), obj.getZ());

    // Scale based on width, height, depth
    glScalef(obj.getWidth(), obj.getHeight(), obj.getDepth());
    
    // For now, always draw a block
    // In a more complete implementation, we would have different object types
    Object3D::block(-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f);

    glPopMatrix();
}

void Render::drawSphereObject(const Object3D& obj)
{
    int tex = obj.getTexture();
    if (tex < 0 || tex > 1)
        tex = 0;

    glBindTexture(GL_TEXTURE_2D, texIDs[tex]);

    glPushMatrix();

    glTranslatef(obj.getX(), obj.getY(), obj.getZ());
    
    // Scale to match the object's size
    glScalef(obj.getWidth(), obj.getHeight(), obj.getDepth());
    
    // Generate and draw sphere
    static Surface sphereSurface;
    static bool initialized = false;
    if (!initialized) {
        Object3D::sphere(sphereSurface);
        initialized = true;
    }
    Object3D::drawSphere(sphereSurface);

    glPopMatrix();
}

void Render::draw(const Scene& scene)
{
   glColor3f(1.0f, 1.0f, 1.0f);
   // Draw objects
   for (const auto& obj : scene.getObjects())
      {
         // For now, always draw as block
         // In a real implementation, we would check the object type
         drawObject(*obj);
      }
}



