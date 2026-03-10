/******************************************************************************************
 *  File Name:      lighting.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Definition of methods necessary for diffuse and ambient terrain lighting 
 *  using a light direction and surface normals.
 * 
 *  Dependencies:
 *  math.h
 * 
 *  Notes:
 *
 ******************************************************************************************/

# pragma once

#include "../core/math.h"

class Lighting
{
    public:
    // constructor
        Lighting();
    
    // setters
        void setLightDirection(const Vec3& dir);
        void setLightColor(const Color& color);
        void setAmbientStrength(float strength);
        void setDiffuseStrength(float strength);

    // getters
        Vec3 getLightDirection() const;
        Color getLightColor() const;

    // functionality
        float computeShade(const Vec3& normal) const;
        Color shadeColor(const Color& baseColor, const Vec3& normal) const;

    private:
        Vec3 lightDirection;
        Color lightColor;

        float ambientStrength;
        float diffuseStrength;


        

};
