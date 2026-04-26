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
