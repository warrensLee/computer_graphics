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


#pragma once

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
            const int idx = index(i, j);
            const float x = (static_cast<float>(j) - halfCols) * spacing;

            X[idx] = x;
            Y[idx] = 0.0f;
            Z[idx] = z;
        }
    }

}


// gets the current index
int Height::index(int i, int j) const
{
    return i * cols + j;
}


// GETTERS:
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


int Height::getSpacing() const
{
    return spacing;
}

