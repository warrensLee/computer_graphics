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

class Render;

class Cube : public Object3D
{
public:
    void draw(Render& renderer) const override;
};
