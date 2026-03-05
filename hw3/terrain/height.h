/******************************************************************************************
 *  File Name:      height.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 3, 2026
 *
 *  Description:
 *  Defintion of commonly used math tools such as clamping, length, minimum, etc.
 * 
 *  Dependencies:
 *  config.h, vector
 * 
 *  Notes:
 *
 ******************************************************************************************/

#pragma once

#include "../core/config.h"
#include <vector>

class Height
{
    public:
        // initializers
        void init(int rows = Config::GRID_ROWS, int cols = Config::GRID_COLS, float spacing = Config::GRID_SPACE);
        void initGrid();
        int index(int i, int j) const;

        // getters
        const std::vector<float>& getX() const;
        const std::vector<float>& getY() const;
        const std::vector<float>& getZ() const;

        int getRows() const;
        int getCols() const;
        float getSpacing() const;

        // functionality
        void buildSurface();

    private:
        // member vairables
        std::vector<float> X, Y, Z;
        int rows, cols;
        float spacing;
};
