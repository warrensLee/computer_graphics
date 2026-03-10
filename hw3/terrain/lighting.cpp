/******************************************************************************************
 *  File Name:      lighting.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Implementation of methods necessary for diffuse and ambient terrain lighting 
 *  using a light direction and surface normals. 
 * 
 *  Dependencies:
 *  lighting.h and all of its dependencies
 * 
 *  Notes:
 *  Ambient and diffuse part of phong lighting is implemented here.
 *  phong lighting = ambient + diffuse + specular
 *  ambient = base amount of light for an object (like 0.5f)
 *  difuse lighting reflects, parallel = most light, perpendicular = least light
 *  need a lightColor and lightSource to be vectors
 *  dot product needed in math.h
 ******************************************************************************************/

#include "lighting.h"

// constructor

Lighting::Lighting()
{
    // this will be applied to our terrain genration
    // basic loghting with smooth loghting
    lightDirection = {0.1f, 1.0f, 0.1f};
    lightDirection = Math::normalize(lightDirection);

    lightColor = {1.0f, 1.0f, 1.0f};

    // this implements a smooth light source
    ambientStrength = 0.2f;
    diffuseStrength = 0.85f;
}


// setters

void Lighting::setLightDirection(const Vec3& dir)
{
    lightDirection = Math::normalize(dir);
}

void Lighting::setLightColor(const Color& color)
{
    lightColor = color;
}

void Lighting::setAmbientStrength(float strength)
{
    ambientStrength = strength;
}

void Lighting::setDiffuseStrength(float strength)
{
    diffuseStrength = strength;
}


// getters

Vec3 Lighting::getLightDirection() const
{
    return lightDirection;
}

Color Lighting::getLightColor() const
{
    return lightColor;
}


// functionality

float Lighting::computeShade(const Vec3& normal) const
{
    // diffuse lighting uses N dot L
    Vec3 N = Math::normalize(normal);
    // already normalized in the constructor
    Vec3 L = lightDirection;

    // N * L
    float ndotl = Math::dotProduct(N, L);

    // clamping logic
    if (ndotl < 0.0f)
    {
        ndotl = 0.0f;
    }

    // finalize shader: ambient + diffuse strenghts times amount of light
    return ambientStrength + diffuseStrength * ndotl;
}

Color Lighting::shadeColor(const Color& baseColor, const Vec3& normal) const
{
    // gets normal brightness
    float brightness = computeShade(normal);

    Color shaded;
    // define the shade color based on our parametes
    shaded.r = baseColor.r * lightColor.r * brightness;
    shaded.g = baseColor.g * lightColor.g * brightness;
    shaded.b = baseColor.b * lightColor.b * brightness;

    // now we need to make sure shading stays within bounds
    if (shaded.r > 1.0f) 
        shaded.r = 1.0f;

    if (shaded.g > 1.0f) 
        shaded.g = 1.0f;

    if (shaded.b > 1.0f) 
        shaded.b = 1.0f;

    return shaded;
}