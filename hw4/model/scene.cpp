/******************************************************************************************
 *  File Name:      scene.cpp
 *  Author:         Warren Roberts
 *  Created:        March 25, 2026
 *  Last Modified:  April 1, 2026
 *
 *  Description:
 *  This is where objects are created and added to a collection of objects
 *  that will be rendered in this project. 
 * 
 *  Dependencies:
 *  scene.h
 * 
 *  Notes:
 *  Unique pointer is used to allow polymorphism in the future, allowing
 *  for a more streamlined OOP structured space. 
 *
 ******************************************************************************************/

#include "scene.h"

// this is where we use methods to create objects
// that will be on screen, adding them to a unique
// pointer vector for future expansion
Scene::Scene()
{
    auto obj1 = std::make_unique<Object3D>();
    obj1->setTexture(0);
    obj1->setPosition(-2.0f, 0.0f, 0.0f);
    obj1->setSize(2.0f, 2.0f, 2.0f);
    addObject(std::move(obj1));

    auto obj2 = std::make_unique<Object3D>();
    obj2->setTexture(1);
    obj2->setPosition(2.0f, 2.0f, 2.0f);
    obj2->setSize(1.5f, 1.5f, 1.5f);
    addObject(std::move(obj2));
}

// add object to the unique pointer vector
void Scene::addObject(std::unique_ptr<Object3D> obj)
{
    objects.push_back(std::move(obj));
}

// returns the objects to be rendered in the
// appropriate area
const std::vector<std::unique_ptr<Object3D>>& Scene::getObjects() const
{
    return objects;
}

