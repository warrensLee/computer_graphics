/******************************************************************************************
 *  File Name:      height.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Declares the Height class used to store terrain grid data and provide
 *  terrain generation methods.
 * 
 *  Dependencies:
 *  math.h and types.h
 * 
 *  Notes:
 *  Acts as the main terrain data model.
 *
 ******************************************************************************************/

#pragma once

#include "../core/math.h"
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
        float getHeightAt(int i, int j) const;
        float getMinHeight() const;
        float getMaxHeight() const;
        float getNormalizedHeightAt(int i, int j) const;

        // setters
        void setMinMax();

        // functionality
        void buildSurface();
        void originalBuildSurface();
        void addNoise();
        void centerHeight();
        void smoothSurface();

        bool hasNeighbor(int i, int j);
        float normalizeHeight(float a) const;

        



    private:
    // member vairables
        std::vector<float> X, Y, Z;
        int rows, cols;
        float spacing;
        float minHeight;
        float maxHeight;
};
