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

#pragma once

#include "object3D.h"
#include "../view/render.h"

class Sphere : public Object3D
{
public:
    void draw(Render& renderer) const override;
};