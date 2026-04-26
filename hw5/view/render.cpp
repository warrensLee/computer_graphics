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
#include "../core/ray_classes.h"

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

    for (const auto& obj : scene.getObjects())
        obj->draw(*this);
}

void Render::tracePixels(const Scene& scene, const Camera& camera,
                         unsigned char* image, int width, int height,
                         const std::string& mode)
{
    Phong shader;

    Point3D cam;
    cam.set(0, 0, -camera.getCameraDistance());
    shader.SetCamera(cam);
    shader.SetLight(scene.getLightColor(), scene.getLightDir());

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int idx = (y * width + x) * 3;
            image[idx] = image[idx+1] = image[idx+2] = 0;

            float xpos = (x - width  / 2) * 2.0f / width;
            float ypos = (y - height / 2) * 2.0f / height;

            Point3D point;
            point.set(xpos, ypos, 0);

            Ray3D ray;
            ray.set(cam, point);

            ColorRGB color;
            Point3D  p;
            Vector3D n;

            for (const auto& obj : scene.getObjects())
            {
                if (obj->intersect(ray, p, n))
                {
                    if (mode == "normal")
                    {
                        color.set(127 + n.vx * 127, 127 + n.vy * 127, 127 + n.vz * 127);
                    }
                    else
                    {
                        shader.SetObject(obj->getColor(), obj->getKa(), obj->getKd(), obj->getKs(), obj->getKp());
                        shader.GetShade(p, n, color);
                    }
                    image[idx]   = (unsigned char)color.R;
                    image[idx+1] = (unsigned char)color.G;
                    image[idx+2] = (unsigned char)color.B;
                    break;
                }
            }
        }
    }
}