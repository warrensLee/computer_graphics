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

void View::drawText(float x, float y, const std::string& s)
{
    glRasterPos2f(x, y); // works in your -1..1 orthographic coords
    for (unsigned char c : s)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

void View::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (model.isGameOver())
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        drawText(-0.20f, 0.0f, "GAME OVER");
    }

    if (model.getPacmanGhostsAte() == 3)
    {
        glColor3f(0.0f,1.0f,0.0f);   // green
        drawText(-0.20f, 0.0f, "YOU HAVE WON!");
    }   


    for (const auto& e : model.getEntities())
        e->display();

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-0.95f, 0.90f,
        "Lives: " + std::to_string(model.getPacmanLives()));

    if (model.getPacmanPower())
        glColor3f(1,0,0);   // red
    else
        glColor3f(0,1,0);   // green


    drawText(-0.95f, 0.80f,
        "Hurt: " + std::string(model.getPacmanHurt() ? "true" : "false"));

    if (model.getPacmanPower())
        glColor3f(0,1,0);   // green
    else
        glColor3f(1,0,0);   // red

    drawText(-0.95f, 0.70f,
        "Power: " + std::string(model.getPacmanPower() ? "true" : "false"));


    // model.pacman.display();

    // for (Ghost &g : model.getGhosts()) // iterate thru each polygon in the vector of polygons
    // {
    //     g.display();
    // }
    // for (Fruit &f : model.getFruit()) // iterate thru each polygon in the vector of polygons
    // {
    //     f.display();
    // }
    // for (Dot &d : model.getDots()) // iterate thru each polygon in the vector of polygons
    // {
    //     d.display();
    // }


}

