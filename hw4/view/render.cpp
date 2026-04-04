/******************************************************************************************
 *  File Name:      render.cpp
 *  Author:         Warren Roberts
 *  Created:        March 25, 2026
 *  Last Modified:  April 3, 2026
 *
 *  Description:
 *  Implements texture initialization and rendering for textured 3D scene objects.
 *  Most of this code was gotten from John Gauch's source code and modified slightly
 *  as needed to fit the project and my design.
 * 
 *  Dependencies:
 *  render.h
 * 
 *  Notes:
 *  Objects are translated, rotated, scaled, and then drawn with their assigned texture.
 *
 ******************************************************************************************/

#include "render.h"
#include "../core/config.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Render::init()
{
    glEnable(GL_TEXTURE_2D);

    Texture::init_texture("textures/brick.jpg", texture1, xdim1, ydim1);
    Texture::init_texture("textures/cannonball.jpg", texture2, xdim2, ydim2);
    Texture::init_texture("textures/basket-ball.jpg", basketballTexture, xdim3, ydim3);
    Texture::init_texture("textures/boards.jpg", groundTexture, xdim4, ydim4);

    glGenTextures(4, texIDs);

    glBindTexture(GL_TEXTURE_2D, texIDs[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim1, ydim1, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1);

    glBindTexture(GL_TEXTURE_2D, texIDs[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim2, ydim2, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2);
    
    glBindTexture(GL_TEXTURE_2D, texIDs[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim3, ydim3, 0, GL_RGB, GL_UNSIGNED_BYTE, basketballTexture);

    glBindTexture(GL_TEXTURE_2D, texIDs[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim4, ydim4, 0, GL_RGB, GL_UNSIGNED_BYTE, groundTexture);

}

void Render::drawCubeGeometry(float xmin, float ymin, float zmin,
                              float xmax, float ymax, float zmax)
{
    float ax = xmin, ay = ymin, az = zmax;
    float bx = xmax, by = ymin, bz = zmax;
    float cx = xmax, cy = ymax, cz = zmax;
    float dx = xmin, dy = ymax, dz = zmax;

    float ex = xmin, ey = ymin, ez = zmin;
    float fx = xmax, fy = ymin, fz = zmin;
    float gx = xmax, gy = ymax, gz = zmin;
    float hx = xmin, hy = ymax, hz = zmin;

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(ax, ay, az);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(bx, by, bz);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(cx, cy, cz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(dx, dy, dz);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(ex, ey, ez);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(ax, ay, az);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(dx, dy, dz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(hx, hy, hz);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(fx, fy, fz);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(ex, ey, ez);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(hx, hy, hz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(gx, gy, gz);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(bx, by, bz);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(fx, fy, fz);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(gx, gy, gz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(cx, cy, cz);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(ax, ay, az);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(ex, ey, ez);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(fx, fy, fz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(bx, by, bz);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(gx, gy, gz);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(cx, cy, cz);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(dx, dy, dz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(hx, hy, hz);
    glEnd();
}

void Render::drawCube(const Object3D& obj)
{
    int tex = obj.getTexture();
    if (tex < 0 || tex > 3)
        tex = 0;

    glBindTexture(GL_TEXTURE_2D, texIDs[tex]);

    glPushMatrix();
    glTranslatef(obj.getX(), obj.getY(), obj.getZ());
    glRotatef(obj.getRotX(), 1.0f, 0.0f, 0.0f);
    glRotatef(obj.getRotY(), 0.0f, 1.0f, 0.0f);
    glRotatef(obj.getRotZ(), 0.0f, 0.0f, 1.0f);
    glScalef(obj.getWidth(), obj.getHeight(), obj.getDepth());

    drawCubeGeometry(-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f);

    glPopMatrix();
}

void Render::drawSphere(const Object3D& obj)
{
    int tex = obj.getTexture();
    if (tex < 0 || tex > 3)
        tex = 0;

    glBindTexture(GL_TEXTURE_2D, texIDs[tex]);

    glPushMatrix();
    glTranslatef(obj.getX(), obj.getY(), obj.getZ());
    glRotatef(obj.getRotX(), 1.0f, 0.0f, 0.0f);
    glRotatef(obj.getRotY(), 0.0f, 1.0f, 0.0f);
    glRotatef(obj.getRotZ(), 0.0f, 0.0f, 1.0f);
    glScalef(obj.getWidth(), obj.getHeight(), obj.getDepth());

    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, 0.5, 30, 30);
    gluDeleteQuadric(quad);

    glPopMatrix();
}

void Render::draw(const Scene& scene)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw ground first
    drawGroundTexture();

    // Draw all scene objects
    for (const auto& obj : scene.getObjects())
    {
        obj->draw(*this);
    }
}

void Render::drawGroundTexture()
{
    // Enable depth testing for proper 3D rendering
    glEnable(GL_DEPTH_TEST);
    
    glBindTexture(GL_TEXTURE_2D, texIDs[3]);

    glBegin(GL_QUADS);

    // draw a ground plane in the x-y plane at z=0.0f (visible to camera at z=20 looking along -Z)
    float groundSize = Config::GROUND_SIZE;  // Make ground larger to be visible
    float groundZ = Config::GROUND_Z_POSITION;
    
    // the ground is in the x-y plane at z=0
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-groundSize, -groundSize, groundZ);
    glTexCoord2f(10.0f, 0.0f); glVertex3f( groundSize, -groundSize, groundZ);
    glTexCoord2f(10.0f, 10.0f); glVertex3f( groundSize,  groundSize, groundZ);
    glTexCoord2f(0.0f, 10.0f); glVertex3f(-groundSize,  groundSize, groundZ);

    glEnd();
}

void Render::drawTrajectoryLine(float startX, float startY, float endX, float endY)
{
    // disable depth testing to ensure the line is always visible
    // and disable texturing for the line
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    
    // set line color to black and
    // set line width to make it more visible
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    
    // draw the line slightly above ground
    glBegin(GL_LINES);
    glVertex3f(startX, startY, 0.1f);  
    glVertex3f(endX, endY, 0.1f);
    glEnd();
    
    // reset line width
    glLineWidth(1.0f);
    
    // re-enable everyhing we disables
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    // reset color to white
    glColor3f(1.0f, 1.0f, 1.0f);
}
