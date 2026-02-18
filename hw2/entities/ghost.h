#ifndef GHOST_H
#define GHOST_H

#include "entity.h"

class Ghost : public Entity
{
    private:
        float direction;

    public:
    // constructors
        Ghost();
        Ghost(float px, float py, float rad, float red, float green, float blue, bool alive = true);
        ~Ghost() override;

    // member methods
        void display() const override;
        void printInformation() const override;

        void setPosition(float fx, float fy);
        bool setAlive(bool a) const;
        void setDirection(float d);


    // member methods
        void update(float dt);
};

#endif // GHOST_H
