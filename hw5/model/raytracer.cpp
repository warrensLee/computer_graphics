#include "raytracer.h"

RayTracer::RayTracer()
{
    position = 2.0f;
    mode = "phong";

    for (int y = 0; y < Config::YDIM; y++)
    {
        for (int x = 0; x < Config::XDIM; x++)
        {
            image[y][x][0] = 0;
            image[y][x][1] = 0;
            image[y][x][2] = 0;
        }
    }
}

void RayTracer::traceScene()
{
    Phong shader;

    Point3D camera;
    camera.set(0, 0, -position);
    shader.SetCamera(camera);

    ColorRGB color;
    color.set(200, 200, 200);

    Vector3D dir;
    dir.set(-1, -1, -1);
    dir.normalize();
    shader.SetLight(color, dir);

    color.set(200, 0, 100);
    shader.SetObject(color, 0.3, 0.4, 0.4, 10);

    Sphere3D sphere;
    Point3D center;
    center.set(0, 0, 3);
    float radius = 2;
    sphere.set(center, radius);

    for (int y = 0; y < Config::YDIM; y++)
    {
        for (int x = 0; x < Config::XDIM; x++)
        {
            image[y][x][0] = 0;
            image[y][x][1] = 0;
            image[y][x][2] = 0;

            float xpos = (x - Config::XDIM / 2) * 2.0f / Config::XDIM;
            float ypos = (y - Config::YDIM / 2) * 2.0f / Config::YDIM;

            Point3D point;
            point.set(xpos, ypos, 0);

            Ray3D ray;
            ray.set(camera, point);

            Point3D p;
            Vector3D n;

            if (sphere.get_intersection(ray, p, n))
            {
                if (mode == "normal")
                {
                    image[y][x][0] = 127 + n.vx * 127;
                    image[y][x][1] = 127 + n.vy * 127;
                    image[y][x][2] = 127 + n.vz * 127;
                }
                else if (mode == "phong")
                {
                    shader.GetShade(p, n, color);
                    image[y][x][0] = color.R;
                    image[y][x][1] = color.G;
                    image[y][x][2] = color.B;
                }
            }
        }
    }
}

void RayTracer::increaseCameraDistance()
{
    if (position < 5.0f)
    {
        position *= 1.1f;
    }
}

void RayTracer::decreaseCameraDistance()
{
    if (position > 1.0f)
    {
        position /= 1.1f;
    }
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