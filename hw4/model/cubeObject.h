/******************************************************************************************
 *  File Name:      cubeObject.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Defines the Cube class, a textured cube object that inherits from Object3D.

 *  Dependencies:
 *  none
 * 
 *  Notes:
 *
 ******************************************************************************************/

#pragma once

#include "object3D.h"
#include "../view/render.h"

class Cube : public Object3D
{
public:
    void draw(Render& renderer) const override;
};