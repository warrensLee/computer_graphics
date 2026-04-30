/******************************************************************************************
 *  File Name:      raytracer.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 27, 2026
 *
 *  Description:
 *  Defines the RayTracer class. This class owns the scene, camera, image buffer,
 *  and calls the Render ray-tracing function to update the image.
 *
 *  Dependencies:
 *  raytracer.h
 *
 *  Notes:
 *  Based on starter ray-tracing code provided by John Gauch.
 *
 ******************************************************************************************/
#pragma once

#include <string>
#include "../core/config.h"
#include "scene.h"
#include "../view/camera.h"
#include "../view/render.h"

class RayTracer
{
public:
    RayTracer();

    void traceScene();
    void updateScene(float dt);

    void increaseCameraDistance();
    void decreaseCameraDistance();

    void setPhongMode();
    void setNormalMode();

    const unsigned char* getImageBuffer() const;

private:
    unsigned char image[Config::YDIM][Config::XDIM][3];
    std::string mode;
    Scene  scene;
    Camera camera;
};
