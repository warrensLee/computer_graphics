/******************************************************************************************
 *  File Name:      3DObject.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 * 
 *  Dependencies:
 *  none
 * 
 *  Notes:
 *
 ******************************************************************************************/
#pragma once

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

class Object3D
{
    public:
    // constructors
        Object3D() = default;

    // objects
        static void block(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);
        static void sphere(Surface &s);


    // get / set
        float getX() const;
        float getY() const;
        float getZ() const;

        float getWidth() const;
        float getHeight() const;
        float getDepth() const;

        int getTexture() const;

        
        void setPosition(float px, float py, float pz);
        void setSize(float w, float h, float d);


        void setTexture(int t);

    private:
        float x, y, z;
        float vx, vy, vz; // velocity
        float pitch, yaw, roll; // rotation angles
        float width, height, depth;
        GLuint textureArray; // OpenGL texture array
        int texture;

};
