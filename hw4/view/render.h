/******************************************************************************************
 *  File Name:      render.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Defines the fucntions necessary to terrain as either a filled surface or wireframe. 
 *  Also includes helper methods for vector math used to calculate surface normals for lighting.
 * 
 *  Dependencies:
 *  gl.h, glut.h height.h, terrainColor.h, lighting.h
 * 
 *  Notes:
 *  Filled terrain uses height-based colors and diffuse lighting.
 *
 ******************************************************************************************/

 #pragma once

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "../model/object3D.h"
#include "../model/scene.h"
#include "../model/texture.h"


class Render
{
    public:
        Render() = default;

        void init();
        void drawObject(const Object3D& obj);
        void draw(const Scene& scene);    
        void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim);


    private:
        unsigned char *texture1 = nullptr;
        unsigned char *texture2 = nullptr;

        int xdim1, ydim1;
        int xdim2, ydim2;

        // store all textures here to quick swap
        GLuint texIDs[2];


        
 
};