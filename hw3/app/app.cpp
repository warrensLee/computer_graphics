/******************************************************************************************
 *  File Name:      app.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Implements the main application flow, including initialization of terrain,
 *  camera, rendering systems, and OpenGL state setup.
 * 
 *  Dependencies:
 *  app.h and all linked subsystems
 * 
 *  Notes:
 *  Coordinates startup behavior before entering the render loop.
 *
 ******************************************************************************************/


#include "app.h"


//********************** Initialization **********************//

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
    height.smoothSurface();


    height.centerHeight();
    height.setMinMax();

    // diagnositics / display confix
    printf("rows=%d cols=%d spacing=%f size=%zu\n",height.getRows(), height.getCols(), height.getSpacing(),height.getX().size());
}

void App::initOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

}


//********************** Functionality **********************//

void App::display()
{
    // printf("display called\n");
    
    // current zoom level
    float zoom = controller.getCamera().getCurrentZoom();
    //printf("zoom = %f"), zoom;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // this will adjust out zoom factor based on what
    // our controller handles the zoom. 
    glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // this is awesome! it sets the camera to what the controller has
    // set it to. so now we can move around with WASD
    glTranslatef(controller.getCamera().getCameraX(), controller.getCamera().getCameraY(), 0.0f);

    glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

    //renderer.drawWireframe(height);
    renderer.drawSurface(height);

    glutSwapBuffers();
}



void App::reshape(int w, int h)
{
    // unused
    (void) w;
    (void) h;
}

void App::keyboard(unsigned char key, int x, int y)
{
    // unused vars
    (void) x;
    (void) y;
    controller.handleKeyDown(key);
    glutPostRedisplay();

}

void App::keyboardKeyUp(unsigned char key, int x, int y)
{
    // unused vars
    (void) x;
    (void) y;
    controller.handleKeyUp(key);
}

void App::idle()
{
    controller.update();
    glutPostRedisplay();
}



//********************** Callbacks **********************//

void App::callKeyboardKeyUp(unsigned char key, int x, int y)
{
    if (instance)
    {
        instance->keyboardKeyUp(key, x, y);
    }
}

void App::callKeyboard(unsigned char key, int x, int y)
{
    if (instance)
    {
        instance->keyboard(key, x, y);
    }
}

void App::callIdle()
{
    if (instance)
    {
        instance->idle();
    }    
}

void App::callDisplay()
{
    if (instance)
    {
        instance->display();
    }
}