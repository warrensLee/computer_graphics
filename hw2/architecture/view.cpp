#include "view.h"


View* View::instance = nullptr;

View::View(Model& m) : model(m)
{
        instance = this;
}

View::~View()
{
    // Nothing here yet
}

void View::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (Entity &e : model.getEntities()) // iterate thru each polygon in the vector of polygons
    {
        e.display();
    }
    for (Dot &d : model.getDots()) // iterate thru each polygon in the vector of polygons
    {
        d.display();
    }

    glutSwapBuffers();
}

void View::displayWrapper()
{
    if (instance) instance->display();
}