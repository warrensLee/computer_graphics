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


void Render::drawSurface(const Height& h)
{
    const auto& X = h.getX();
    const auto& Y = h.getY();
    const auto& Z = h.getZ();
    const int rows = h.getRows();
    const int cols = h.getCols();

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < rows - 1; ++i)
    {
        for (int j = 0; j < cols - 1; ++j)
        {
            // get the correct hieght per corner
            int topLeft = h.index(i, j);
            int topRight = h.index(i, j + 1);
            int bottomLeft = h.index(i + 1, j);
            int bottomRight = h.index(i + 1, j + 1);

            // get normalized heights 
            float heightOne = h.getNormalizedHeightAt(i, j);
            float heightTwo = h.getNormalizedHeightAt(i, j + 1);
            float heightThree = h.getNormalizedHeightAt(i + 1, j);
            float heightFour = h.getNormalizedHeightAt(i + 1, j + 1);
            
            // get all colors 
            Color colorOne = terrainColor.getColorAt(heightOne);
            Color colorTwo = terrainColor.getColorAt(heightTwo);
            Color colorThree = terrainColor.getColorAt(heightThree);
            Color colorFour = terrainColor.getColorAt(heightFour);

            // triangle 1
            glColor3f(colorOne.r, colorOne.g, colorOne.b);
            glVertex3f(X[topLeft], Y[topLeft], Z[topLeft]);

            glColor3f(colorThree.r, colorThree.g, colorThree.b);
            glVertex3f(X[bottomLeft], Y[bottomLeft], Z[bottomLeft]);

            glColor3f(colorTwo.r, colorTwo.g, colorTwo.b);
            glVertex3f(X[topRight], Y[topRight], Z[topRight]);

            // triangle 2
            glColor3f(colorTwo.r, colorTwo.g, colorTwo.b);
            glVertex3f(X[topRight], Y[topRight], Z[topRight]);

            glColor3f(colorThree.r, colorThree.g, colorThree.b);
            glVertex3f(X[bottomLeft], Y[bottomLeft], Z[bottomLeft]);

            glColor3f(colorFour.r, colorFour.g, colorFour.b);
            glVertex3f(X[bottomRight], Y[bottomRight], Z[bottomRight]);
        }
    }

    glEnd();
}



// original method of rendering with a wireframe
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