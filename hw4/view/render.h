/******************************************************************************************
 *  File Name:      render.h
 *  Author:         Warren Roberts
 *  Created:        March 25, 2026
 *  Last Modified:  April 2, 2026
 *
 *  Description:
 *  Defines the Render class, which initializes textures and draws textured
 *  3D objects stored in the scene.
 * 
 *  Dependencies:
 *  OpenGL, GLUT, object3D.h, scene.h, texture.h
 * 
 *  Notes:
 *  This class handles texture setup and rendering only.
 *
 ******************************************************************************************/

#pragma once

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "../model/object3D.h"
#include "../model/sphereObject.h"
#include "../model/cubeObject.h"

#include "../model/scene.h"
#include "../model/texture.h"

class Scene;
class Render
{
public:
    Render() = default;

    void init();
    void draw(const Scene& scene);

    void drawCube(const Object3D& obj);
    void drawSphere(const Object3D& obj);
    void drawGroundTexture();


private:
    void drawCubeGeometry(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);

    unsigned char* texture1 = nullptr;
    unsigned char* texture2 = nullptr;  
    unsigned char* cannonballTexture = nullptr;
    unsigned char* groundTexture = nullptr;


    int xdim1 = 0, ydim1 = 0;
    int xdim2 = 0, ydim2 = 0;
    int xdim3 = 0, ydim3 = 0;
    int xdim4 = 0, ydim4 = 0;

    GLuint texIDs[3];
};