/******************************************************************************************
 *  File Name:      scene.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 3, 2026
 *
 *  Description:
 *  This is where objects are created and added to a collection of objects
 *  that will be rendered in this project. Physics and updates are also handled here.
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
#include <cstdlib>
#include <ctime>

// create initial scene objects

Scene::Scene()
{
    // seed random number generator for rotation speeds
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // create a cube object
    auto cube = std::make_unique<Cube>();
    cube->setTexture(0);
    cube->setPosition(-5.0f, -2.0f, 0.0f);
    cube->setSize(3.0f, 3.0f, 3.0f);
    cube->setRotationSpeed(0.0f, 20.0f, 0.0f);
    addObject(std::move(cube));

    // create a sphere object
    auto sphere = std::make_unique<Sphere>();
    sphere->setTexture(1);
    sphere->setPosition(5.0f, -2.0f, 0.0f);
    sphere->setSize(4.0f, 4.0f, 4.0f);
    sphere->setRotationSpeed(15.0f, 10.0f, 0.0f);
    addObject(std::move(sphere));
}

// add object to the unique pointer vector
void Scene::addObject(std::unique_ptr<Object3D> obj)
{
    objects.push_back(std::move(obj));
}

// returns the objects to be rendered in the
// appropriate area
const std::vector<std::unique_ptr<Object3D>> &Scene::getObjects() const
{
    return objects;
}

void Scene::update(float dt)
{
    // iterate through objects and update their positions based on velocity and rotation speed
    for (auto it = objects.begin(); it != objects.end(); )
    {
        // update each object
        (*it)->update(dt);
        ++it;
    }
}



