/******************************************************************************************
 *  File Name:      cubeObject.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 1, 2026
 *
 *  Description:
 *  Defines the Cube class, a textured cube object that inherits from Object3D.

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

class Cube : public Object3D
{
    public:
        void draw(Render& renderer) const override;
        void setGeometry(Point3D center, float radius);
        void setPosition(float px, float py, float pz);
        bool intersect(Ray3D ray, Point3D& p, Vector3D& n) const override;
    private:
        mutable Cube3D geometry;

};
