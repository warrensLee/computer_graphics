/******************************************************************************************
 *  File Name:      app.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  February 26, 2026
 *
 *  Description:
 *  Defintion of commonly used math tools such as clamping, length, minimum, etc.
 * 
 *  Dependencies:
 *  app.h, glut.h, gl.h
 * 
 *  Notes:
 *
 ******************************************************************************************/

#include "app.h"



App* App::instance = nullptr;

App::App() : renderer(height), controller()
{

}

void App::init()
{
    instance = this;

    // this will establish our terrain once and forall
    // applies all effects that bring our terrain to life

    height.init();
    height.initGrid();
    height.buildSurface();
    height.addNoise();
    height.smoothSurface();

    // now to apply coloring
    // .................... //

    // diagnositics / display confix
    printf("rows=%d cols=%d spacing=%f size=%zu\n",
       height.getRows(), height.getCols(), height.getSpacing(),
       height.getX().size());
    printf("p0: %f %f %f\n", height.getX()[0], height.getY()[0], height.getZ()[0]);
    printf("plast: %f %f %f\n",
        height.getX().back(), height.getY().back(), height.getZ().back());
        
}

void App::initOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(-z, z, -z, z, -z, z);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(-2, 2, -2, 2, -2, 2);
    // //glScalef(0.7f, 0.7f, 0.7f);         // to get a better view of the grid

    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

}

void App::display()
{
    // printf("display called\n");
    
    // current zoom level
    float zoom = controller.getCurrentZoom();
    //printf("zoom = %f"), zoom;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    renderer.drawWireframe(height);

    glutSwapBuffers();
}

void App::callDisplay()
{
    if (instance)
        instance->display();
}

void App::reshape(int w, int h)
{
    (void) w;
    (void) h;
}

void App::keyboard(unsigned char key, int x, int y)
{
    (void) x;
    (void) y;
    controller.handleKey(key);
    glutPostRedisplay();

}

void App::callKeyboard(unsigned char key, int x, int y)
{
    if (instance)
        instance->keyboard(key, x, y);
}


void App::idle()
{

}
