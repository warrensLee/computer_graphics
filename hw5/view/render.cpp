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

static bool traceClosestObject(const Scene& scene, Ray3D ray,
                               Point3D origin,
                               Point3D& closestP,
                               Vector3D& closestN,
                               const Object3D*& closestObj)
{
    bool hit = false;
    float closestDist = 1e9f;

    for (const auto& obj : scene.getObjects())
    {
        Point3D tempP;
        Vector3D tempN;

        if (obj->intersect(ray, tempP, tempN))
        {
            float dx = tempP.px - origin.px;
            float dy = tempP.py - origin.py;
            float dz = tempP.pz - origin.pz;
            float dist = dx * dx + dy * dy + dz * dz;

            if (dist > 0.001f && dist < closestDist)
            {
                closestDist = dist;
                closestP = tempP;
                closestN = tempN;
                closestObj = obj.get();
                hit = true;
            }
        }
    }

    return hit;
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

            Point3D closestP;
            Vector3D closestN;
            const Object3D* closestObj = nullptr;

            bool hit = traceClosestObject(scene, ray, cam, closestP, closestN, closestObj);
            
            if (hit && closestObj)
            {
                if (mode == "normal")
                {
                    color.set(127 + closestN.vx * 127,
                            127 + closestN.vy * 127,
                            127 + closestN.vz * 127);
                }
                else
                {
                    ColorRGB surfaceColor = closestObj->getSurfaceColor(closestP);

                    shader.SetObject(
                        surfaceColor,
                        closestObj->getKa(),
                        closestObj->getKd(),
                        closestObj->getKs(),
                        closestObj->getKp()
                    );

                    shader.GetShade(closestP, closestN, color);
                    Vector3D D = ray.dir;
                    D.normalize();

                    Vector3D N = closestN;
                    N.normalize();

                    float dotDN = D.dot(N);

                    Vector3D reflectDir;
                    reflectDir.set(
                        D.vx - 2.0f * dotDN * N.vx,
                        D.vy - 2.0f * dotDN * N.vy,
                        D.vz - 2.0f * dotDN * N.vz
                    );
                    reflectDir.normalize();

                    Point3D reflectStart;
                    reflectStart.set(
                        closestP.px + reflectDir.vx * 0.01f,
                        closestP.py + reflectDir.vy * 0.01f,
                        closestP.pz + reflectDir.vz * 0.01f
                    );

                    Ray3D reflectRay;
                    reflectRay.set(reflectStart, reflectDir);

                    Point3D reflectP;
                    Vector3D reflectN;
                    const Object3D* reflectObj = nullptr;

                    if (traceClosestObject(scene, reflectRay, reflectStart, reflectP, reflectN, reflectObj))
                    {
                        ColorRGB reflectColor = reflectObj->getSurfaceColor(reflectP);

                        reflectColor.mult(closestObj->getKs());
                        color.add(reflectColor);
                        color.clamp();
                    }
                    
                }

                image[idx]   = (unsigned char)color.R;
                image[idx+1] = (unsigned char)color.G;
                image[idx+2] = (unsigned char)color.B;
            }
            else
            {
                ColorRGB sky;

                // simple blue sky
                sky.set(70, 100, 255);

                image[idx]   = (unsigned char)sky.R;
                image[idx+1] = (unsigned char)sky.G;
                image[idx+2] = (unsigned char)sky.B;
            }
        }
    }
}