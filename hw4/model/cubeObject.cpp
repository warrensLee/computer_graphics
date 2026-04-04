/******************************************************************************************
 *  File Name:      cubeObject.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 1, 2026
 *
 *  Description:
 *  Implements Cube drawing method
 * 
 *  Dependencies:
 *  cubeObject.h, render.h
 * 
 *  Notes:
 *
 ******************************************************************************************/

#include "cubeObject.h"
#include "../view/render.h"

void Cube::draw(Render& renderer) const
{
    renderer.drawCube(*this);
}
