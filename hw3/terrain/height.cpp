/******************************************************************************************
 *  File Name:      height.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  February 26, 2026
 *
 *  Description:
 *  Define methods and initialize grid of our polygons that will form a terrain.
 * 
 *  Dependencies:
 *  height.h, 
 * 
 *  Notes:
 *
 ******************************************************************************************/


#include "height.h"


// to reserve grid size
void Height::init(int rows, int cols, float spacing)
{
    this->rows = rows;
    this->cols = cols;
    this->spacing = spacing;

    X.resize(size_t(rows) * size_t(cols));
    Y.resize(size_t(rows) * size_t(cols));
    Z.resize(size_t(rows) * size_t(cols));
}


// will fill the grid after the sizes are reserved
void Height::initGrid()
{
    // centering logic to fill the grid from the middle
    const float halfCols = 0.5f * static_cast<float>(cols - 1);
    const float halfRows = 0.5f * static_cast<float>(rows - 1);

    for (int i = 0; i < rows; ++i)
    {
        // prevents calculating this over and over
        const float z = (static_cast<float>(i) - halfRows) * spacing;

        for (int j = 0; j < cols; ++j)
        {
            // prevents over calculations
            const int idx = index(i, j);
            const float x = (static_cast<float>(j) - halfCols) * spacing;

            X[idx] = x;
            Y[idx] = 0.0f;
            Z[idx] = z;
        }
    }

}

// getters:

int Height::index(int i, int j) const
{
    return i * cols + j;        // gets the current index
}

const std::vector<float>& Height::getX() const
{
    return X;
}


const std::vector<float>& Height::getY() const
{
    return Y;
}


const std::vector<float>& Height::getZ() const
{
    return Z;
}


int Height::getRows() const
{
    return rows;
}


int Height::getCols() const
{
    return cols;
}


float Height::getSpacing() const
{
    return spacing;
}

float Height::getMinHeight() const
{
    float min = Y[0];

    for (float y : Y)
    {
        if (y < min)
        {
            min = y;
        }
    }

    return min;
}

float Height::getMaxHeight() const
{
    float max = Y[0];

    for (float y : Y)
    {
        if (y > max)
        {
            max = y;
        }
    }

    return max;
}

float Height::normalizeHeight(float a) const
{
    return (a - minHeight) / (maxHeight - minHeight);   
}

float Height::getHeightAt(int i, int j) const
{
    return Y[index(i, j)];
}

float Height::getNormalizedHeightAt(int i, int j) const
{
    if (maxHeight == minHeight)
    {
        return 0.0f;
    }
    return normalizeHeight(Y[index(i, j)]);
}


// setters
void Height::setMinMax()
{
    minHeight = getMinHeight();
    maxHeight= getMaxHeight();
}


// functionality:


// this will initialize x and y coords
// then based on those values create
// y coordinated that bring our surface 
// to life!
void Height::buildSurface()
{
    const float scale = 0.4f;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // gets the current index based on i and j
            int idx = index(i, j);
            
            // initial setting of X and Z
            float x = X[idx];
            float z = Z[idx];

            // now apply the scale and base terrain surface
            // (sin(x * 2) * cos(z * 4) is my base surface
            // also tried (sin(z * 2) * cos(x * 4) * 1.7
            Y[idx] = scale * (sin(z * 2) * cos(x * 4)) * 1.7f; //* (z/x/2);
            //Y[idx] = scale * exp(sin(x*z));
        }
    }
}



// noise to add realism and randomness
// to our terrain.
// occurs after base surface is created
void Height::addNoise()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // gets the current index based on i and j
            int idx = index(i, j);

            // adds noise to each y-coordinate
            Y[idx] += Math::getRandomBetween(-0.05, 0.05f);
        }
    }
}

// 3 X 3 averaging to smooth the terrain
// applied after noise.
void Height::smoothSurface()
{
    // to set it all smoothly at the end
    // temporarily jolding all Y values
    std::vector<float> temporaryY = Y;

    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < cols - 1; ++j)
        {
            int idx = index(i, j);

            // if all neighbors required out present:
            //
            //  A B C
            //  D E F
            //  G H I
            //
            // E must have all of these neighbors

            if (hasNeighbor(i, j))
            {
                // now get the correct index based on x and y
                float A = Y[index(i-1, j-1)];
                float B = Y[index(i-1, j)];
                float C = Y[index(i-1, j+1)];
                float D = Y[index(i,   j-1)];
                float E = Y[index(i,   j)];
                float F = Y[index(i,   j+1)];
                float G = Y[index(i+1, j-1)];
                float H = Y[index(i+1, j)];
                float I = Y[index(i+1, j+1)];

                temporaryY[idx] = (A + B + C + D + E + F + G + H + I) / 9.0f;
            }
        }
    }

    Y = temporaryY;
}

// helper fucntion for smoothSurface to checidx if
// there are all the required neighbors to smooth
bool Height::hasNeighbor(int i, int j)
{
    if (i > 0 && i < rows - 1 && j > 0 && j < cols - 1)
    {
        return true;
    }


    return false;
}

