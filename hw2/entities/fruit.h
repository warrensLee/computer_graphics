#ifndef FRUIT_H
#define FRUIT_H


#include "entity.h"

class Fruit : public Entity
{
    private:
        float direction;

    public:
    // constructors
        Fruit();
        Fruit(float px, float py, float rad, float red, float green, float blue, bool alive = true);
        ~Fruit() override;

    // member methods
        void display() const override;
        void printInformation() const override;

        void setPosition(float fx, float fy);
        bool setAlive(bool a) const;
        void setDirection(float d);


    // member methods
        void update(float dt) override;
        void wrap() override;

};

#endif // FRUIT_H
