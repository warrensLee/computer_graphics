/******************************************************************************************
 *  File Name:      scene.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 3, 2026
 *
 *  Description:
 *  This is where methods and data structures relevant to the scene are
 *  defined.
 *
 *  Dependencies:
 *  memory, vector, object3D, cubeObject, sphereObject
 *
 *  Notes:
 *  Unique pointer is used to allow polymorphism in the future, allowing
 *  for a more streamlined OOP structured space.
 *
 ******************************************************************************************/

#pragma once

#include "object3D.h"
#include "../core/config.h"
#include "../core/ray_classes.h"
#include "cubeObject.h"
#include "sphereObject.h"
#include <vector>
#include <memory>

class Scene
{
public:
    Scene();

    void update(float dt);

    void addObject(std::unique_ptr<Object3D> obj);

    const std::vector<std::unique_ptr<Object3D>>& getObjects() const;

    ColorRGB getLightColor() const;
    Vector3D getLightDir() const;

private:
    std::vector<std::unique_ptr<Object3D>> objects;

    ColorRGB lightColor;
    Vector3D lightDir;
};
