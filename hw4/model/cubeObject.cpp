/******************************************************************************************
 *  File Name:      cubeObject.h
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

#include "cubeObject.h"

void Cube::draw(Render& renderer) const
{
    renderer.drawCube(*this);
}
