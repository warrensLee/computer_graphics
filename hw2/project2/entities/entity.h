#ifndef ENTITY_H
#define ENTITY_H


#include <cmath>
#include "../components/polygon.h"
#include "../components/gl_platform.h"
#include <random>

struct Bounds { float left, right, bottom, top; };    

class Entity : public Polygon
{
protected:
    float x,y; 
    float radius;
    float r, g, b;
    bool isAlive;
    std::mt19937 rng;
    float vx = 0.0f;
    float vy = 0.0f;
    float speed = .5f;
    float direction;
    float dirX;
    float dirY;
    float changeTimer;
    float nextChangeTime;
    float halfW, halfH; // half extents
public:
    // constructors
    Entity();
    Entity(float px, float py, float radius, float red, float green, float blue, bool alive = true);
    virtual ~Entity();


    float randFloatInRange(float high, float low);
    int randInt(int high, int low);
    void pickRandDirection();

    // member functions
    void printInformation() const override;
    virtual void display() const override;

    // setters
    void setPosition(float sx, float sy);
    void setAlive(bool a);
    void setColor(float sr, float sg, float sb);
    void setSpeed(float s);
    void setDirection(float radians);

    // getters
    float getR() const;
    float getG() const;
    float getB() const;
    float getX() const;
    float getY() const;
    float getRadius() const;
    bool getAlive() const;
    float getSpeed() const;
    Bounds getBounds() const;


    // traversal
    void setVelocity(float nvx, float nvy);
    void move(float dt);
    virtual void wrap();
    virtual void update(float dt);

    virtual void onCollide(Entity& other) = 0;

    // second dispatch targets
    virtual void collideWith(class Pacman& p);
    virtual void collideWith(class Ghost& g);
    virtual void collideWith(class Fruit& f);
    //virtual void collideWith(class Dot&);

};

#endif // ENTITY_H
