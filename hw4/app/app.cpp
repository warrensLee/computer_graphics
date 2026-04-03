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

App::App() : renderer(), controller(), scene()
{
    instance = this;

}

void App::init()
{
    initOpenGL();
    renderer.init();
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

    renderer.draw(scene);

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

void App::mouseButton(int button, int state, int x, int y)
{
    controller.mouseButton(button, state, x, y);
}

void App::mouseMotion(int x, int y)
{
    controller.mouseMotion(x, y);
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

void App::callMouseButton(int button, int state, int x, int y)
{
    if (instance)
    {
        printf("calling mouse button");
        instance->mouseButton(button, state, x, y);
    }    
}

void App::callMouseMotion(int x, int y)
{
    if (instance)
    {
        printf("calling mouse motion");
        instance->mouseMotion(x, y);
    }
}

void App::callLaunchProjectile(float launchVX, float launchVY, float distance)
{
    printf("launching projectile");
    instance->scene.launchProjectile(launchVX, launchVY, distance);

}
