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

#include "plane3D.h"

bool Plane3D::getIntersection(const Ray3D& ray, Point3D& p, Vector3D& n)
{

}

ColorRGB Plane3D::getColorAt(const Point3D& p)
{
    int checkerX = floor(p.px * scale);
    int checkerZ = floor(p.pz * scale);

    if ((checkerX + checkerZ) % 2 == 0)
    {
        color.set(255, 255, 255);
    }
    else
    {
       color.set(30, 30, 30);
    }
}

Plane3D::drawPlane()
{

}