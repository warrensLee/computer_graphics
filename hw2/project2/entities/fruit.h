#ifndef FRUIT_H
#define FRUIT_H


#include "entity.h"

class Fruit : public Entity
{
    private:

    public:
    // constructors
        Fruit();
        Fruit(float px, float py, float rad, float red, float green, float blue, bool alive = true);
        ~Fruit() override;

    // member methods
        void display() const override;
        void printInformation() const override;

        void setPosition(float fx, float fy);
        void setAlive(bool a);

        void onCollide(Entity& other) override { other.collideWith(*this); }

        // second dispatch targets
        void collideWith(class Pacman& p) override;
        void collideWith(class Ghost& g) override;
        void collideWith(class Fruit& f) override;
        //void collideWith(class Dot&) override;


    // member methods
        void update(float dt) override;
        void wrap() override;

};

#endif // FRUIT_H
