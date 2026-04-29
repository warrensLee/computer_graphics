/******************************************************************************************
 *  File Name:      plane3D.cpp
 *  Author:         Warren Roberts
 *  Created:        April 25, 2026
 *  Last Modified:  April 26, 2026
 *
 *  Description:
 *  Handles plane intersection logic for ray tracing and generates a checkerboard pattern
 *  based on where the ray hits the plane.
 *
 *  Dependencies:
 *  plane3D.h
 *
 *  Notes:
 *  Uses basic ray-plane intersection math and alternates colors using tile indexing.
 *
 ******************************************************************************************/
#include "plane3D.h"
#include <cmath>

Plane3D::Plane3D()
{
}

void Plane3D::setPlane(Point3D p, Vector3D n, ColorRGB c1, ColorRGB c2, float tile)
{
    point = p;
    normal = n;
    normal.normalize();
    color1 = c1;
    color2 = c2;
    tileSize = tile;

    if (tile <= 0.0f)
        tileSize = 1.0f;
    else
        tileSize = tile;
}

bool Plane3D::getIntersection(const Ray3D& ray, Point3D &hitPoint, Vector3D &hitNormal) const
{
    // dot product between ray direction and plane normal
    float denom = ray.dir.vx * normal.vx +
                  ray.dir.vy * normal.vy +
                  ray.dir.vz * normal.vz;

    // if denom is near zero, the ray is basically parallel → no hit
    const float epsilon = 1e-6f;
    if (std::fabs(denom) < epsilon)
        return false;

    // solve for t using standard ray-plane formula
    float dx = point.px - ray.point.px;
    float dy = point.py - ray.point.py;
    float dz = point.pz - ray.point.pz;
    float t = (dx * normal.vx + dy * normal.vy + dz * normal.vz) / denom;

    // ignore hits behind the camera or too close to avoid noise
    if (t < 0.001f)
        return false;

    // compute exact hit location
    hitPoint.px = ray.point.px + t * ray.dir.vx;
    hitPoint.py = ray.point.py + t * ray.dir.vy;
    hitPoint.pz = ray.point.pz + t * ray.dir.vz;

    // plane normal stays constant everywhere
    hitNormal = normal;

    return true;
}

ColorRGB Plane3D::getCheckerColor(Point3D hitPoint)
{
    // figure out which tile we are in using x and z
    int ix = static_cast<int>(std::floor(hitPoint.px / tileSize));
    int iz = static_cast<int>(std::floor(hitPoint.pz / tileSize));

    // alternate colors like a checkerboard
    if ((ix + iz) % 2 == 0)
        return color1;
    else
        return color2;
}

ColorRGB Plane3D::getSurfaceColor(Point3D hitPoint) const
{
    int ix = static_cast<int>(std::floor(hitPoint.px / tileSize));
    int iz = static_cast<int>(std::floor(hitPoint.pz / tileSize));

    if (std::abs(ix + iz) % 2 == 0)
    {
        return color1;
    }
    else
    {
        return color2;
    }
}

void Plane3D::draw(Render &renderer) const
{
}

float Plane3D::getKa() const
{
    return 0.3f;
}
float Plane3D::getKd() const
{
    return 0.4f;
}
float Plane3D::getKs() const
{
    return 0.4f;
}
float Plane3D::getKp() const
{
    return 10.0f;
}

bool Plane3D::intersect(Ray3D ray, Point3D &hitPoint, Vector3D &hitNormal) const
{
    return getIntersection(ray, hitPoint, hitNormal);
}
