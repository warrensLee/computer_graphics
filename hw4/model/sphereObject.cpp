/******************************************************************************************
 *  File Name:      sphereObject.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
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
