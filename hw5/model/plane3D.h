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

#include "object3D.h"
#include "../core/ray_classes.h"

class Plane3D : public Object3D
{
public:
    Plane3D();
    Point3D point;
    Vector3D normal;
    ColorRGB color1;
    ColorRGB color2;
    float tileSize;

    void setPlane(Point3D p, Vector3D n, ColorRGB c1, ColorRGB c2, float tile);
    bool getIntersection(const Ray3D& ray, Point3D &hitPoint, Vector3D &hitNormal) const;
    ColorRGB getCheckerColor(Point3D hitPoint);
    ColorRGB getSurfaceColor(Point3D hitPoint) const override;
    bool intersect(const Ray3D& ray, Point3D &hitPoint, Vector3D &hitNormal) const override;
    float getKa() const;
    float getKd() const;
    float getKs() const;
    float getKp() const;

    void draw(Render &renderer) const override;
};
