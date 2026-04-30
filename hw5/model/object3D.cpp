/******************************************************************************************
 *  File Name:      object3D.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 27, 2026
 *
 *  Description:
 *  Implements the Object3D class, including getters, setters, and motion updates.
 *
 *  Dependencies:
 *  object3D.h
 *
 *  Notes:
 *  This file does not handle drawing. Rendering is handled separately.
 *
 ******************************************************************************************/

#include "object3D.h"

class Render;

void Object3D::update(float dt)
{
   x += vx * dt;
   y += vy * dt;
   z += vz * dt;

   rx += rvx * dt;
   ry += rvy * dt;
   rz += rvz * dt;
}

bool Object3D::intersect(Ray3D ray, Point3D &p, Vector3D &n) const
{
    return false;
}

float Object3D::getX() const
{
   return x;
}

float Object3D::getY() const
{
   return y;
}

float Object3D::getZ() const
{
   return z;
}

float Object3D::getVX() const
{
   return vx;
}

float Object3D::getVY() const
{
   return vy;
}

float Object3D::getVZ() const
{
   return vz;
}

float Object3D::getRotX() const
{
   return rx;
}

float Object3D::getRotY() const
{
   return ry;
}

float Object3D::getRotZ() const
{
   return rz;
}

float Object3D::getRotVX() const
{
   return rvx;
}

float Object3D::getRotVY() const
{
   return rvy;
}

float Object3D::getRotVZ() const
{
   return rvz;
}

float Object3D::getWidth() const
{
   return width;
}

float Object3D::getHeight() const
{
   return height;
}

float Object3D::getDepth() const
{
   return depth;
}

void Object3D::setPosition(float px, float py, float pz)
{
   x = px;
   y = py;
   z = pz;
}

void Object3D::setVelocity(float vx_, float vy_, float vz_)
{
   vx = vx_;
   vy = vy_;
   vz = vz_;
}

void Object3D::setRotation(float rx_, float ry_, float rz_)
{
   rx = rx_;
   ry = ry_;
   rz = rz_;
}

void Object3D::setRotationSpeed(float rvx_, float rvy_, float rvz_)
{
   rvx = rvx_;
   rvy = rvy_;
   rvz = rvz_;
}

void Object3D::setSize(float w, float h, float d)
{
   width = w;
   height = h;
   depth = d;
}

ColorRGB Object3D::getColor() const
{
   return color;
}
float Object3D::getKa() const
{
   return Ka;
}
float Object3D::getKd() const
{
   return Kd;
}
float Object3D::getKs() const
{
   return Ks;
}
float Object3D::getKp() const
{
   return Kp;
}

void Object3D::setMaterial(ColorRGB c, float ka, float kd, float ks, float kp)
{
   color = c;
   Ka = ka;
   Kd = kd;
   Ks = ks;
   Kp = kp;
}

ColorRGB Object3D::getSurfaceColor(Point3D hitPoint) const
{
   return color;
}