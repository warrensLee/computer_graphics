#include "controller.h"


Controller* Controller::instance = nullptr;

Controller::Controller(Model& m, View& v) : model(m), view(v)
{
    instance = this;
}

Controller::~Controller()
{
    // Nothing here yet
}
void Controller::keyboard(unsigned char key, int x, int y)
{
    std::printf("key=%d char=%c\n", key, key);
    std::fflush(stdout);

    if (key == 27 || key == 'q')
        // close program
        std::exit(0);
    if (key == 'w')
        // move north
        model.pacman.changeDirection(PI / 2.0f);
    if (key == 'a')
        // move west
        model.pacman.changeDirection(PI);
    if (key == 's')
        // move south
        model.pacman.changeDirection(3.0f * PI / 2.0f);
    if (key == 'd')
        // move east
        model.pacman.changeDirection(0.0f);
}

void Controller::keyDown(unsigned char key, int x, int y)
{

    if (key == 27 || key == 'q')
        // close program
        std::exit(0);
    if (key == 'w')
    {
        model.pacman.moveUp = true;
    }
    if (key == 's')
    {
        model.pacman.moveDown = true;
        }
    if (key == 'a') 
    {
        model.pacman.moveLeft = true;
    }
    if (key == 'd')
    {
        model.pacman.moveRight = true;
    }
}

void Controller::keyUp(unsigned char key, int x, int y)
{
    if (key == 'w')
    {
        model.pacman.moveUp = false;
    }
    if (key == 's')
    {
        model.pacman.moveDown = false;
        }
    if (key == 'a') 
    {
        model.pacman.moveLeft = false;
    }
    if (key == 'd')
    {
        model.pacman.moveRight = false;
    }
}
