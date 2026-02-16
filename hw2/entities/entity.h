#ifndef ENTITY_H
#define ENTITY_H


#include <cmath>
#include "../components/polygon.h"

class Entity : public Polygon
{
private:
    float radius;
    bool isAlive;
    float r, g, b, x, y;
public:
    // constructors
    Entity();
    Entity(float px, float py, float radius, float red, float green, float blue, bool alive = true);
    virtual ~Entity();

    // member functions
    void printInformation() const override;
    void setPosition(float sx, float sy);
    void setColor(float sr, float sg, float sb);
    void display() const override;
    float getR() const;
    float getG() const;
    float getB() const;
    float getX() const;
    float getY() const;
    float getRadius() const;
    bool getAlive() const;
	void setAlive(bool a);

};

#endif // ENTITY_H
