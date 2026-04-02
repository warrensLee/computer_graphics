/******************************************************************************************
 *  File Name:      sphereObject.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 * 
 *  Dependencies:
 *  none
 * 
 *  Notes:
 *
 ******************************************************************************************/

#include "sphereObject.h"

void Sphere::draw(Render& renderer) const
{
    renderer.drawSphere(*this);
}