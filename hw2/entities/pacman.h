#ifndef PACMAN_H
#define PACMAN_H

#include "entity.h"

class Pacman : public Entity
{
    private:
        float radius;
        float mouthAngle;
        float px, py;

    public:
    // constructors
        Pacman();
        Pacman(float px, float py, float r, float mouth, float red, float green, float blue);

    // member methods
        void display() const;
        void setPosition(float fx, float fy);
        bool setAlive(bool a) const;
        bool getAlive() const;

};

#endif // PACMAN_H
