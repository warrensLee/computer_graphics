/******************************************************************************************
 *  File Name:      render.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  February 26, 2026
 *
 *  Description:
 *  Defintion of commonly used math tools such as clamping, length, minimum, etc.
 * 
 *  Dependencies:
 *
 *  Notes:
 *
 ******************************************************************************************/

#include "render.h"

Render::Render(Height & height) : h(height)
{

}

void Render::drawWireframe(const Height& h)
{
    const auto& X = h.getX();
    const auto& Y = h.getY();
    const auto& Z = h.getZ();
    const int rows = h.getRows();
    const int cols = h.getCols();

    glBegin(GL_LINES);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            const int k = h.index(i, j);

            // right neighbor
            if (j + 1 < cols)
            {
                const int kr = h.index(i, j + 1);
                glVertex3f(X[k],  Y[k],  Z[k]);
                glVertex3f(X[kr], Y[kr], Z[kr]);
            }

            // down neighbor
            if (i + 1 < rows)
            {
                const int kd = h.index(i + 1, j);
                glVertex3f(X[k],  Y[k],  Z[k]);
                glVertex3f(X[kd], Y[kd], Z[kd]);
            }
        }
    }

    glEnd();
}