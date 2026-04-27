/******************************************************************************************
 *  File Name:      plane3D.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 1, 2026
 *
 *  Description:
 *  Implements Plane3D methods for ray tracing: intersection and checkerboard color.

 *  Dependencies:
 *  plane3D.h
 * 
 *  Notes:
 *
 ******************************************************************************************/

#include "plane3D.h"
#include <cmath>

void Plane3D::set(Point3D p, Vector3D n, ColorRGB c1, ColorRGB c2, float tile)
{
    point = p;
    normal = n;
    color1 = c1;
    color2 = c2;
    tileSize = tile;
}

bool Plane3D::get_intersection(Ray3D ray, Point3D &hitPoint, Vector3D &hitNormal)
{
    // compute denominator = dot(ray.dir, normal)
    float denom = ray.dir.vx * normal.vx +
                  ray.dir.vy * normal.vy +
                  ray.dir.vz * normal.vz;

    // if ray is parallel to plane (|denom| < epsilon)
    const float epsilon = 1e-6f;
    if (std::fabs(denom) < epsilon)
        return false;

    // compute t = dot(point - ray.point, normal) / denom
    float dx = point.px - ray.point.px;
    float dy = point.py - ray.point.py;
    float dz = point.pz - ray.point.pz;
    float t = (dx * normal.vx + dy * normal.vy + dz * normal.vz) / denom;

    // reject if t is behind the ray origin (or too close)
    if (t < 0.001f)
        return false;

    // compute hit point
    hitPoint.px = ray.point.px + t * ray.dir.vx;
    hitPoint.py = ray.point.py + t * ray.dir.vy;
    hitPoint.pz = ray.point.pz + t * ray.dir.vz;

    // normal is the plane's normal (assumed already normalized)
    hitNormal = normal;

    return true;
}

ColorRGB Plane3D::get_checker_color(Point3D hitPoint)
{
    // compute integer tile coordinates based on hitPoint's x and z
    int ix = static_cast<int>(std::floor(hitPoint.px / tileSize));
    int iz = static_cast<int>(std::floor(hitPoint.pz / tileSize));

    // even sum -> color1, odd sum -> color2
    if ((ix + iz) % 2 == 0)
        return color1;
    else
        return color2;
}
