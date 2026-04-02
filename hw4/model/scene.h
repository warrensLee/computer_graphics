/******************************************************************************************
 *  File Name:      scene.h
 *  Author:         Warren Roberts
 *  Created:        March 25, 2026
 *  Last Modified:  April 1, 2026
 *
 *  Description:
 *  This is where methods and data structures relevant to the scene are
 *  defined.
 * 
 *  Dependencies:
 *  memory, vector, object3D
 * 
 *  Notes:
 *  Unique pointer is used to allow polymorphism in the future, allowing
 *  for a more streamlined OOP structured space.
 *
 ******************************************************************************************/

#pragma once

#include "object3D.h"
#include<vector>
#include <memory>       // for unique_ptr

class Scene
{
    public:
    // constructors
        Scene();

        void update();

        void addObject(std::unique_ptr<Object3D> obj);



        const std::vector<std::unique_ptr<Object3D>>& getObjects() const;


    private:
        // unique_ptr for possible polymorphism in the future
        std::vector<std::unique_ptr<Object3D>> objects;



};
