#ifndef FRUIT_H
#define FRUIT_H


#include "../components/polygon.h"

class Fruit : public Polygon
{
private:
    bool isAlive;
public:
    // constructors
    Fruit();
    Fruit(float fx, float fy, float size, float r, float g, float b, bool alive = true);

    // member functions
    void display() const;
	void setPosition(float fx, float fy);
	bool setAlive(bool a) const;
    bool getAlive() const;

};

#endif // FRUIT_H
