#ifndef PACMAN_H
#define PACMAN_H

#include "entity.h"

class Fruit;
class Ghost;

static constexpr float PI = 3.14159265358979323846f; //ensures this number is made once on compilation!

class Pacman : public Entity
{
    private:
        float mouthAngle;               // how wide his mouth opens
        float mouthSpeed;               // how fast his mouth opens
        bool mouthOpening;              // if mouth is open: true
        //float speed;                    // how fast he moves
        float direction;                // what direction he faces
        bool hasEaten = false;
        float powerTimer = 0.0f;
        const float powerDuration = 3.5f;
        bool hurt = false;
        float hurtTimer = 0.0f;
        const float hurtDuration = 3.0f;
        int currentLives = 3;
        const int maxLives = 3;
        int ghostsAte = 0;


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
        bool getHasEaten() const;
        int getLives() const;
        bool getPower() const;
        bool getHurt() const;
        int getGhostsAte() const;


        float getMouthAngle() const;                  // return current mouth angle
        void setMouthOpening(bool open);        // will start mouth opening by changing bool value
        void setMouthAngle(float angle);        // will update the angle mouth is open for animation
        void setHasEaten(bool h);
        void setAlive(bool a);

        void update(float dt) override;
        void wrap() override;


        void onCollide(Entity& other) override { other.collideWith(*this); }

        // second dispatch targets
        void collideWith(class Pacman& p) override;
        void collideWith(class Ghost& g) override;
        void collideWith(class Fruit& f) override;
        //void collideWith(class Dot&) override;


    // to control movement directions
        bool moveUp = false;
        bool moveDown = false;
        bool moveLeft = false;
        bool moveRight = false;
};

#endif // PACMAN_H
