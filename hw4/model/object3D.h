/******************************************************************************************
 *  File Name:      object3D.h
 *  Author:         Warren Roberts
 *  Created:        March 25, 2026
 *  Last Modified:  April 2, 2026
 *
 *  Description:
 *  Defines the Object3D class, which stores the position, velocity, rotation,
 *  size, and texture index for an object in the scene.
 * 
 *  Dependencies:
 *  none
 * 
 *  Notes:
 *  This class is responsible for object state and update behavior only.
 *  Rendering should be handled by the Render class.
 *
 ******************************************************************************************/

#pragma once

// forward declaration to avoid circular dependency
class Render;

class Object3D
{
public:
    Object3D() = default;
    virtual ~Object3D() = default;

    virtual void draw(Render& renderer) const = 0;
    virtual void update(float dt);

    // position
    float getX() const;
    float getY() const;
    float getZ() const;
    void setPosition(float px, float py, float pz);

    // velocity
    float getVX() const;
    float getVY() const;
    float getVZ() const;
    void setVelocity(float vx_, float vy_, float vz_);

    // rotation
    float getRotX() const;
    float getRotY() const;
    float getRotZ() const;
    void setRotation(float rx_, float ry_, float rz_);

    // rotation speed
    float getRotVX() const;
    float getRotVY() const;
    float getRotVZ() const;
    void setRotationSpeed(float rvx_, float rvy_, float rvz_);

    // size
    float getWidth() const;
    float getHeight() const;
    float getDepth() const;
    void setSize(float w, float h, float d);

    // texture
    int getTexture() const;
    void setTexture(int t);



private:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    float vx = 0.0f;
    float vy = 0.0f;
    float vz = 0.0f;

    float rx = 0.0f;
    float ry = 0.0f;
    float rz = 0.0f;

    float rvx = 0.0f;
    float rvy = 0.0f;
    float rvz = 0.0f;

    float width = 1.0f;
    float height = 1.0f;
    float depth = 1.0f;

    int texture = 0;
    
    float gravity = -0.02f;
};