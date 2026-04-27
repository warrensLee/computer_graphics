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

class Plane3D
{
    public:
        bool getIntersection(const Ray3D& ray, Point3D& p, Vector3D& n);
        ColorRGB getColorAt(const Point3D& p);

        void drawPlane();
        


    private:
        float scale = 2.0f;

};
