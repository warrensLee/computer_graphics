#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../components/gl_platform.h"
#include "model.h"
#include "view.h"

#include <iostream>
#include <cstdlib>

class Controller
{
private:
    Model& model;
    View& view;

public:
    // constructor
    static Controller* instance;
    Controller();
    Controller(Model& m, View& v);

    // destructor
    ~Controller();

    // methods
    void keyboard(unsigned char key, int x, int y);
    static void keyboardWrapper(unsigned char key, int x, int y);


};




#endif // CONTROLLER_H
