/******************************************************************************************
 *  File Name:      raytracer.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 27, 2026
 *
 *  Description:
 *  Implements the RayTracer class. This class owns the scene, camera, image buffer,
 *  and calls the Render ray-tracing function to update the image.
 *
 *  Dependencies:
 *  raytracer.h
 *
 *  Notes:
 *  Based on starter ray-tracing code provided by John Gauch.
 *
 ******************************************************************************************/

#include "raytracer.h"

RayTracer::RayTracer() : scene(), camera()
{
    mode = "phong";
    for (int y = 0; y < Config::YDIM; y++)
        for (int x = 0; x < Config::XDIM; x++)
            image[y][x][0] = image[y][x][1] = image[y][x][2] = 0;
}

void RayTracer::updateScene(float dt)
{
    scene.update(dt);
}

void RayTracer::traceScene()
{
    Render::tracePixels(scene, camera, &image[0][0][0], Config::XDIM, Config::YDIM, mode);
}

void RayTracer::increaseCameraDistance()
{
    camera.increaseCameraDistance();
}

void RayTracer::decreaseCameraDistance()
{
    camera.decreaseCameraDistance();
}

void RayTracer::setPhongMode()
{
    mode = "phong";
}

void RayTracer::setNormalMode()
{
    mode = "normal";
}

const unsigned char* RayTracer::getImageBuffer() const
{
    return &image[0][0][0];
}
