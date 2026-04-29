/******************************************************************************************
 *  File Name:      sphereObject.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 1, 2026
 *
 *  Description:
 *  Implements Sphere drawing method
 * 
 *  Dependencies:
 *  sphereObject.h, render.h
 * 
 *  Notes:
 *
 ******************************************************************************************/

#include "sphereObject.h"
#include "../view/render.h"

void Sphere::draw(Render& renderer) const
{
    renderer.drawSphere(*this);
}

void Sphere::setGeometry(Point3D center, float radius)
{
    geometry.set(center, radius);
}

void Sphere::setPosition(float px, float py, float pz)
{
    Object3D::setPosition(px, py, pz);
    // update the Sphere3D geometry center to match the new position
    geometry.center.set(px, py, pz);
}

bool Sphere::intersect(Ray3D ray, Point3D& p, Vector3D& n) const
{
    return geometry.get_intersection(ray, p, n);
}
