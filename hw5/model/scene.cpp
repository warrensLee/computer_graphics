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

    // Gray sphere centered at (0,0,3)
    auto graySphere = std::make_unique<Sphere>();
    Point3D centerGray;
    centerGray.set(0, 0, 3);
    graySphere->setGeometry(centerGray, 1.5f);
    ColorRGB grayColor;
    grayColor.set(180, 180, 180);
    graySphere->setMaterial(grayColor, 0.3f, 0.4f, 0.4f, 10.0f);
    addObject(std::move(graySphere));

    // Yellow sphere near the gray sphere
    auto yellowSphere = std::make_unique<Sphere>();
    Point3D centerYellow;
    centerYellow.set(2, 0, 3);
    yellowSphere->setGeometry(centerYellow, 1.0f);
    ColorRGB yellowColor;
    yellowColor.set(255, 255, 0);
    yellowSphere->setMaterial(yellowColor, 0.3f, 0.4f, 0.4f, 10.0f);
    addObject(std::move(yellowSphere));
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
