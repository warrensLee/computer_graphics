/******************************************************************************************
 *  File Name:      height.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Implements terrain height generation, grid initialization, smoothing,
 *  noise application, and terrain height normalization.
 * 
 *  Dependencies:
 *  height.h
 * 
 *  Notes:
 *  Stores the terrain grid and builds the heightmap used for rendering.
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
    // this normalized height will be used as a divisor
    // and this will keep us from dividing by 0
    if (maxHeight == minHeight)
    {
        return 0.0f;
    }
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
void Height::originalBuildSurface()
{
    const float scale = 1.3f;

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
            Y[idx] = scale * (sin(x*2) * cos(z*3)); //* (z/x/2);
            //Y[idx] = scale * exp((sin(x * 2) * cos(z * 4)) * 1.2f);
        }
    }
}


void Height::buildSurface()
{
    // this is the scale for our whole terrain
    // changing it will change everything easily!
    const float terrainScale = 0.35;
    // I want to make a centered large mountain base in the center
    // so first I will get the center positions
    const float halfWidth = (cols - 1) * spacing * 0.5f;
    const float halfDepth = (rows - 1) * spacing * 0.5f;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int idx = index(i, j);

            float x = X[idx];
            float z = Z[idx];

            float sampleX = x * terrainScale;
            float sampleZ = z * terrainScale;

            // make them relative to the current x
            float nx = x / halfWidth;
            float nz = z / halfDepth;

            // explain to me what this does
            float dist = std::sqrt(nx * nx + nz * nz);

            // clamp out of bounds values
            float centerMask = 1.0f - dist;
            if (centerMask < 0.0f)
            {
                centerMask = 0.0f;
            }
            
            // changing the power will give us a steeper mountain
            centerMask = std::pow(centerMask, 2.5f);

            // now to make one central mountain base
            float baseNoise = Math::octavePerlin(sampleX, sampleZ, 5, 0.5f, 2.0f);

            // secondary detail around the mountain
            float hillNoise = Math::octavePerlin(sampleX * 2.0f, sampleZ * 2.0f, 4, 0.5f, 2.0f);

            // adds finer detail on the mountain
            float mountainNoise = Math::octavePerlin(sampleX * 1.3f, sampleZ * 1.3f, 5, 0.5f, 2.0f);

            // makes mountains more ridged
            float ridged = 1.0f - std::fabs(mountainNoise);
            ridged *= ridged;

            // convert from roughly [-1,1] to [0,1]
            float baseNoise01 = 0.5f * (baseNoise + 1.0f);
            float hillNoise01 = 0.5f * (hillNoise + 1.0f);

            // now with all of our terrain features we must add them to the height
            // this will combine everything we made above
            float height = 0.0f;

            height += baseNoise01 * centerMask * 9.0f;
            height += hillNoise01 * 3.0f;
            height += ridged * 1.5f;

            // actually sets height
            Y[idx] = height;
        }
    }
    setMinMax();
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
            Y[idx] += Math::getRandomBetween(0.05f, 0.3f);
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

// used to center our terrain so that
// excessive zooming isnt made to find
// the terrain after launch
void Height::centerHeight()
{
    setMinMax();

    float mid = (minHeight + maxHeight) * 0.5f;

    for (float& y : Y)
    {
        y -= mid;
    }

    setMinMax();
}