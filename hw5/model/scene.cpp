/******************************************************************************************
 *  File Name:      scene.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 22, 2026
 *
 *  Description:
 *  Creates and owns the ray-tracing scene: one sphere object and a directional light.
 *
 *  Dependencies:
 *  scene.h
 *
 *  Notes:
 *  Unique pointer is used to allow polymorphism in the future.
 *
 ******************************************************************************************/

#include "scene.h"

Scene::Scene()
{
    lightColor.set(200, 200, 200);
    lightDir.set(-1, -1, -1);
    lightDir.normalize();

    auto sphere = std::make_unique<Sphere>();
    Point3D center;
    center.set(0, 0, 3);
    sphere->setGeometry(center, 2.0f);
    ColorRGB color;
    color.set(255, 255, 0);
    sphere->setMaterial(color, 0.3f, 0.4f, 0.4f, 10.0f);
    addObject(std::move(sphere));
}

void Scene::addObject(std::unique_ptr<Object3D> obj)
{
    objects.push_back(std::move(obj));
}

const std::vector<std::unique_ptr<Object3D>>& Scene::getObjects() const
{
    return objects;
}

void Scene::update(float dt)
{
    for (auto& obj : objects)
        obj->update(dt);
}

ColorRGB Scene::getLightColor() const
{
    return lightColor;
}

Vector3D Scene::getLightDir() const
{
    return lightDir;
}
