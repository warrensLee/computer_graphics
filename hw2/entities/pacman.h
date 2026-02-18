#ifndef PACMAN_H
#define PACMAN_H

#include "entity.h"

static constexpr float PI = 3.14159265358979323846f; //ensures this number is made once on compilation!

class Pacman : public Entity
{
    private:
        float mouthAngle;               // how wide his mouth opens
        float mouthSpeed;               // how fast his mouth opens
        bool mouthOpening;              // if mouth is open: true
        //float speed;                    // how fast he moves
        float direction;                // what direction he faces


    public:
    // constructors
        Pacman();
        Pacman(float px, float py, float rad, float red, float green, float blue, bool alive = true);
        ~Pacman() override;
    // member methods
        void display() const override;
        void printInformation() const override;

        void changeDirection(float d);
        float getDirection() const;

        float getMouthAngle() const;                  // return current mouth angle
        void setMouthOpening(bool open);        // will start mouth opening by changing bool value
        void setMouthAngle(float angle);        // will update the angle mouth is open for animation

        void update(float dt);


    // to control movement directions
        bool moveUp = false;
        bool moveDown = false;
        bool moveLeft = false;
        bool moveRight = false;
};

#endif // PACMAN_H
