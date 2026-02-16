#ifndef VIEW_H
#define VIEW_H

#include "../components/gl_platform.h"
#include "../components/polygon.h"
#include "../entities/entity.h"
#include "model.h"

class View
{
private:
    Model& model;

public:
    // Constructor
    View(Model& m);
    static View* instance;

    // Destructor
    ~View();
    void display();
    static void displayWrapper();

};

#endif // VIEW_H
