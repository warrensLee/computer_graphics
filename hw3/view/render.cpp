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

Render::Render(Height & height) : h(height), terrainColor()
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

            float height1 = h.getNormalizedHeightAt(i, j);
            Color color1 = terrainColor.getColorAt(height1);

            // right neighbor
            if (j + 1 < cols)
            {
                const int kr = h.index(i, j + 1);

                float heightRight = h.getNormalizedHeightAt(i, j + 1);
                Color colorRight = terrainColor.getColorAt(heightRight);

                glColor3f(color1.r, color1.g, color1.b);
                glVertex3f(X[k], Y[k], Z[k]);

                glColor3f(colorRight.r, colorRight.g, colorRight.b);
                glVertex3f(X[kr], Y[kr], Z[kr]);
            }

            // down neighbor
            if (i + 1 < rows)
            {
                const int kd = h.index(i + 1, j);

                float heightDown = h.getNormalizedHeightAt(i + 1, j);
                Color colorDown = terrainColor.getColorAt(heightDown);

                glColor3f(color1.r, color1.g, color1.b);
                glVertex3f(X[k], Y[k], Z[k]);

                glColor3f(colorDown.r, colorDown.g, colorDown.b);
                glVertex3f(X[kd], Y[kd], Z[kd]);
            }
        }
    }

    glEnd();
}