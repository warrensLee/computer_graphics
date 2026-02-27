#ifndef VIEW_H
#define VIEW_H

#include "../components/gl_platform.h"


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

    static void drawText(float x, float y, const std::string& s);

};

#endif // VIEW_H
