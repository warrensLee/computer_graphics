/******************************************************************************************
 *  File Name:      plane3D.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 1, 2026
 *
 *  Description:
 *  Defines the Plane3D class for ray tracing: a plane with checkerboard pattern.

 *  Dependencies:
 *  ray_classes.h
 * 
 *  Notes:
 *
 ******************************************************************************************/

#pragma once

#include "../core/ray_classes.h"

class Plane3D
{
public:
    Point3D  point;
    Vector3D normal;
    ColorRGB color1;
    ColorRGB color2;
    float    tileSize;

    void set(Point3D p, Vector3D n, ColorRGB c1, ColorRGB c2, float tile);
    bool get_intersection(Ray3D ray, Point3D &hitPoint, Vector3D &hitNormal);
    ColorRGB get_checker_color(Point3D hitPoint);
};
