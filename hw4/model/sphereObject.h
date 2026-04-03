/******************************************************************************************
 *  File Name:      sphereObject.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
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

class Render;

class Sphere : public Object3D
{
public:
    void draw(Render& renderer) const override;
};
