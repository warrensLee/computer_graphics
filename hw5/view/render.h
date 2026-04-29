/******************************************************************************************
 *  File Name:      render.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 22, 2026
 *
 *  Description:
 *  Declares the Render class, which blits the ray-traced pixel buffer to the screen.
 *
 *  Dependencies:
 *  OpenGL, GLUT
 *
 *  Notes:
 *  All rendering output is produced by RayTracer; this class only handles display.
 *
 ******************************************************************************************/

#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif
// #include <OpenGL/gl.h>
// #include <GLUT/glut.h>
#include <string>

#include "../model/scene.h"
#include "../model/object3D.h"
#include "camera.h"

class Render
{
public:
    Render() = default;
    void drawRayTracedImage(const unsigned char* buf, int w, int h);
    void draw(const Scene& scene);

    void drawCube(const Object3D& obj);
    void drawSphere(const Object3D& obj);
    void drawCubeGeometry(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);

    static void tracePixels(const Scene& scene, const Camera& camera,
                            unsigned char* image, int width, int height,
                            const std::string& mode);
};
