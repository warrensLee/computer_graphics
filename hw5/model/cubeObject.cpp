/******************************************************************************************
 *  File Name:      cubeObject.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 29, 2026
 *
 *  Description:
 *  Implements Cube drawing method
 *
 *  Dependencies:
 *  cubeObject.h, render.h
 *
 *  Notes:
 *
 ******************************************************************************************/

#include "cubeObject.h"
#include "../view/render.h"

void Cube::draw(Render &renderer) const
{
    renderer.drawCube(*this);
}

void Cube::setGeometry(Point3D center, float radius)
{
    geometry.set(center, radius);
}

void Cube::setPosition(float px, float py, float pz)
{
    Object3D::setPosition(px, py, pz);
    // update the cube3D geometry center to match the new position
    geometry.center.set(px, py, pz);
}

bool Cube::intersect(Ray3D ray, Point3D &p, Vector3D &n) const
{
    float angle = -getRotY() * M_PI / 180.0f;
    float c = cos(angle);
    float s = sin(angle);

    Point3D localPoint;
    localPoint.set(geometry.center.px + c * (ray.point.px - geometry.center.px) - s * (ray.point.pz - geometry.center.pz), ray.point.py, geometry.center.pz + s * (ray.point.px - geometry.center.px) + c * (ray.point.pz - geometry.center.pz));

    Vector3D localDir;
    localDir.set(c * ray.dir.vx - s * ray.dir.vz, ray.dir.vy, s * ray.dir.vx + c * ray.dir.vz);

    Ray3D localRay;
    localRay.set(localPoint, localDir);

    Point3D localHit;
    Vector3D localNormal;

    if (!geometry.get_intersection(localRay, localHit, localNormal))
    {
        return false;
    }

    angle = getRotY() * M_PI / 180.0f;
    c = cos(angle);
    s = sin(angle);

    p.set(geometry.center.px + c * (localHit.px - geometry.center.px) - s * (localHit.pz - geometry.center.pz), localHit.py, geometry.center.pz + s * (localHit.px - geometry.center.px) + c * (localHit.pz - geometry.center.pz));

    n.set(c * localNormal.vx - s * localNormal.vz, localNormal.vy, s * localNormal.vx + c * localNormal.vz);
    n.normalize();

    return true;
}