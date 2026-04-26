/******************************************************************************************
 *  File Name:      sphereObject.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 1, 2026
 *
 *  Description:
 *  Defines the Sphere class, a textured sphere object that inherits from Object3D.
 * 
 *  Dependencies:
 *  object3D.h
 * 
 *  Notes:
 *
 ******************************************************************************************/

#pragma once

#include "object3D.h"
#include "../core/ray_classes.h"

class Render;

class Sphere : public Object3D
{
public:
    void draw(Render& renderer) const override;
    void setGeometry(Point3D center, float radius);
    void setPosition(float px, float py, float pz) override;
    bool intersect(Ray3D ray, Point3D& p, Vector3D& n) const override;

private:
    mutable Sphere3D geometry;
};
