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
#include <cmath>

Scene::Scene()
{
    lightColor.set(200, 200, 200);
    lightDir.set(-1, -1, -1);
    lightDir.normalize();
    orbitAngle = 0.0f;
    yellowSpherePtr = nullptr;

    // Gray sphere positioned at (0,0,3)
    auto graySphere = std::make_unique<Sphere>();
    Point3D positionGraySphere;
    positionGraySphere.set(0, 0, 20);
    graySphere->setGeometry(positionGraySphere, 1.6f);
    ColorRGB grayColor;
    grayColor.set(180, 180, 180);
    graySphere->setMaterial(grayColor, 0.3f, 0.4f, 0.4f, 10.0f);
    addObject(std::move(graySphere));

    // Yellow sphere near the gray sphere
    auto yellowSphere = std::make_unique<Sphere>();
    Point3D positionYellowSphere;
    positionYellowSphere.set(3.0f, 0.0f, 20.0f);
    yellowSphere->setGeometry(positionYellowSphere, 1.5f);
    ColorRGB yellowColor;
    yellowColor.set(255, 255, 0);
    yellowSphere->setMaterial(yellowColor, 0.3f, 0.4f, 0.4f, 10.0f);
    yellowSpherePtr = yellowSphere.get();  // store pointer before move
    addObject(std::move(yellowSphere));

    auto checkeredPlane = std::make_unique<Plane3D>();
    Point3D positionPlane;
    positionPlane.set(0.0f, 5.0f, 20.0f);
    Vector3D vectorPlane;
    vectorPlane.set(0.0f,1.0f,0.0f);
    ColorRGB planeYellow;
    planeYellow.set(255, 255, 0);
    ColorRGB planeRed;
    planeRed.set(255, 0, 0);
    float tile = 2.0f;
    checkeredPlane->setPlane(positionPlane, vectorPlane, planeYellow, planeRed, tile);
    addObject(std::move(checkeredPlane));

    auto cubeOne = std::make_unique<Cube>();
    Point3D positionCubeOne;
    positionCubeOne.set(10.0f, 1.0f, 20.0f);    
    cubeOne->setGeometry(positionCubeOne, 2.0f);    
    ColorRGB cubeOneColor;
    cubeOneColor.set(0, 255, 0);
    cubeOne->setMaterial(cubeOneColor, 0.3f, 0.4f, 0.4f, 10.0f);
    cubeOnePtr = cubeOne.get();  // store pointer before move
    addObject(std::move(cubeOne));

    auto cubeTwo = std::make_unique<Cube>();
    Point3D positionCubeTwo;
    positionCubeTwo.set(-10.0f, 1.0f, 20.0f);
    cubeTwo->setGeometry(positionCubeTwo, 2.0f);    
    ColorRGB cubeTwoColor;
    cubeTwoColor.set(255, 0, 0);
    cubeTwo->setMaterial(cubeTwoColor, 0.3f, 0.4f, 0.4f, 10.0f);
    cubeTwoPtr = cubeTwo.get();  // store pointer before move
    addObject(std::move(cubeTwo));

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
    orbitAngle += dt * 1.50f;

    if (yellowSpherePtr)
    {
        float orbitRadius = 3.5f;

        float positionX = 0.0f;
        float positionY = 0.8f;
        float positionZ = 20.0f;   // same as gray sphere

        float x = positionX + orbitRadius * cos(orbitAngle);
        float z = positionZ + orbitRadius * sin(orbitAngle);

        yellowSpherePtr->setPosition(x, positionY, z);
    }

    if (cubeOnePtr)
    {
        cubeOnePtr->setRotation(cubeOnePtr->getRotX(), cubeOnePtr->getRotY() + dt * 60.0f, cubeOnePtr->getRotZ());
    }

    if (cubeTwoPtr)
    {
        cubeTwoPtr->setRotation(cubeTwoPtr->getRotX(), cubeTwoPtr->getRotY() - dt * 75.0f, cubeTwoPtr->getRotZ());
    }

    for (auto& obj : objects)
    {
        obj->update(dt);
    }
}

ColorRGB Scene::getLightColor() const
{
    return lightColor;
}

Vector3D Scene::getLightDir() const
{
    return lightDir;
}
