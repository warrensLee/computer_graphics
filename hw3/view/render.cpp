/******************************************************************************************
 *  File Name:      render.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Renders the terrain as either a filled surface or wireframe. Also includes helper
 *  methods for vector math used to calculate surface normals for lighting.
 * 
 *  Dependencies:
 *  render.h and its dependencies
 * 
 *  Notes:
 *  Filled terrain uses height-based colors and diffuse lighting.
 *
 ******************************************************************************************/


#include "render.h"

Render::Render(Height & height) : h(height), terrainColor(), lighting()
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
            int topLeft   = h.index(i, j);
            int topRight   = h.index(i, j + 1);
            int bottomLeft = h.index(i + 1, j);
            int bottomRight  = h.index(i + 1, j + 1);

            float heightOne   = h.getNormalizedHeightAt(i, j);
            float heightTwo   = h.getNormalizedHeightAt(i, j + 1);
            float heightThree = h.getNormalizedHeightAt(i + 1, j);
            float heightFour  = h.getNormalizedHeightAt(i + 1, j + 1);

            Color colorOne   = terrainColor.getAlpineColor(heightOne);
            Color colorTwo   = terrainColor.getAlpineColor(heightTwo);
            Color colorThree = terrainColor.getAlpineColor(heightThree);
            Color colorFour  = terrainColor.getAlpineColor(heightFour);

            // triangle 1: one, three, two
            Vec3 normal1 = getSurfaceNormal(X, Y, Z, topLeft, bottomLeft, topRight);

            Color shadedOne   = lighting.shadeColor(colorOne, normal1);
            Color shadedThree = lighting.shadeColor(colorThree, normal1);
            Color shadedTwo   = lighting.shadeColor(colorTwo, normal1);

            glColor3f(shadedOne.r, shadedOne.g, shadedOne.b);
            glVertex3f(X[topLeft], Y[topLeft], Z[topLeft]);

            glColor3f(shadedThree.r, shadedThree.g, shadedThree.b);
            glVertex3f(X[bottomLeft], Y[bottomLeft], Z[bottomLeft]);

            glColor3f(shadedTwo.r, shadedTwo.g, shadedTwo.b);
            glVertex3f(X[topRight], Y[topRight], Z[topRight]);

            // triangle 2: two, three, four
            Vec3 normal2 = getSurfaceNormal(X, Y, Z, topRight, bottomLeft, bottomRight);

            Color shadedTwoB   = lighting.shadeColor(colorTwo, normal2);
            Color shadedThreeB = lighting.shadeColor(colorThree, normal2);
            Color shadedFour   = lighting.shadeColor(colorFour, normal2);

            glColor3f(shadedTwoB.r, shadedTwoB.g, shadedTwoB.b);
            glVertex3f(X[topRight], Y[topRight], Z[topRight]);

            glColor3f(shadedThreeB.r, shadedThreeB.g, shadedThreeB.b);
            glVertex3f(X[bottomLeft], Y[bottomLeft], Z[bottomLeft]);

            glColor3f(shadedFour.r, shadedFour.g, shadedFour.b);
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

Vec3 Render::makeVec3(float x, float y, float z)
{
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Vec3 Render::subtractVec3(const Vec3& a, const Vec3& b)
{
    Vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

Vec3 Render::getSurfaceNormal(const std::vector<float>& X, const std::vector<float>& Y, const std::vector<float>& Z, int a, int b, int c)
{
    Vec3 p1 = makeVec3(X[a], Y[a], Z[a]);
    Vec3 p2 = makeVec3(X[b], Y[b], Z[b]);
    Vec3 p3 = makeVec3(X[c], Y[c], Z[c]);

    Vec3 t1 = subtractVec3(p2, p1);
    Vec3 t2 = subtractVec3(p3, p1);

    Vec3 normal = Math::crossProduct(t1, t2);
    return Math::normalize(normal);
}