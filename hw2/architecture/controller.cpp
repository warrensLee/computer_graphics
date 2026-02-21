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
void Controller::mouse(int button, int state, int x, int y)
{
    float glX = (2.0f * x / 750) - 1.0f;
    float glY = 1.0f - (2.0f * y / 750);
    std::cout << "clicked x: " << glX << " y: " << glY << "\n";
    model.getPacman().setMouseTarget(glX, glY);

}
void Controller::keyboard(unsigned char key, int x, int y)
{
    // removes warning for unused parameters
    // forced signature from OpenGL
    (void)x;
    (void)y;

    std::printf("key=%d char=%c\n", key, key);
    std::fflush(stdout);

    if (key == 27 || key == 'q')
        // close program
        std::exit(0);
    if (key == 'w')
        // move north
        model.getPacman().changeDirection(PI / 2.0f);
    if (key == 'a')
        // move west
        model.getPacman().changeDirection(PI);
    if (key == 's')
        // move south
        model.getPacman().changeDirection(3.0f * PI / 2.0f);
    if (key == 'd')
        // move east
        model.getPacman().changeDirection(0.0f);
}

void Controller::keyDown(unsigned char key, int x, int y)
{
    // removes warning for unused parameters
    // forced signature from OpenGL
    (void)x;
    (void)y;

    if (key == 27 || key == 'q')
        // close program
        std::exit(0);
    if (key == 'w')
    {
        model.getPacman().moveUp = true;
    }
    if (key == 's')
    {
        model.getPacman().moveDown = true;
        }
    if (key == 'a') 
    {
        model.getPacman().moveLeft = true;
    }
    if (key == 'd')
    {
        model.getPacman().moveRight = true;
    }
}

void Controller::keyUp(unsigned char key, int x, int y)
{
    // removes warning for unused parameters
    // forced signature from OpenGL
    (void)x;
    (void)y;

    if (key == 'w')
    {
        model.getPacman().moveUp = false;
    }
    if (key == 's')
    {
        model.getPacman().moveDown = false;
        }
    if (key == 'a') 
    {
        model.getPacman().moveLeft = false;
    }
    if (key == 'd')
    {
        model.getPacman().moveRight = false;
    }
}
