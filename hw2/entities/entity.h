#ifndef ENTITY_H
#define ENTITY_H


#include <cmath>
#include "../components/polygon.h"
#include "../components/gl_platform.h"


class Entity : public Polygon
{
protected:
    float x,y; 
    float radius;
    float r, g, b;
    bool isAlive;
    float vx = 0.0f;
    float vy = 0.0f;
    float speed = .5f;
public:
    // constructors
    Entity();
    Entity(float px, float py, float radius, float red, float green, float blue, bool alive = true);
    virtual ~Entity();

    // member functions
    void printInformation() const override;
    virtual void display() const override;

    // setters
    void setPosition(float sx, float sy);
    void setAlive(bool a);
    void setColor(float sr, float sg, float sb);
    void setSpeed(float s);

    // getters
    float getR() const;
    float getG() const;
    float getB() const;
    float getX() const;
    float getY() const;
    float getRadius() const;
    bool getAlive() const;
    float getSpeed() const;


    // traversal
    void setVelocity(float nvx, float nvy);
    void move(float dt);
    virtual void wrap();
    virtual void update(float dt);

};

#endif // ENTITY_H
