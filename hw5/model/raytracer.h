#pragma once

#include <string>
#include "../core/config.h"
#include "../core/ray_classes.h"

class RayTracer
{
    public:
        RayTracer();

        void traceScene();

        void increaseCameraDistance();
        void decreaseCameraDistance();

        void setPhongMode();
        void setNormalMode();

        const unsigned char* getImageBuffer() const;

    private:
        unsigned char image[Config::YDIM][Config::XDIM][3];
        float position;
        std::string mode;
};