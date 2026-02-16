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
        std::exit(0);
    if (key == 'a')
        // move west
        std::exit(0);
    if (key == 's')
        // move south
        std::exit(0);
    if (key == 'd')
        // move east
        std::exit(0);
}

void Controller::keyboardWrapper(unsigned char key, int x, int y) 
{
    if (instance) instance->keyboard(key, x, y);
}