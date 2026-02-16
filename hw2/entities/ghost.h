#ifndef GHOST_H
#define GHOST_H

#include "entity.h"

class Ghost : public Entity
{
    private:
        float radius;
        float mouthAngle;
        float px, py;

    public:
    // constructors
        Ghost();
        Ghost(float px, float py, float r, float mouth, float red, float green, float blue);

    // member methods
        void display() override;
        void printInformation() override;
        void setPosition(float fx, float fy);
        bool setAlive(bool a) const;
};

#endif // GHOST_H
