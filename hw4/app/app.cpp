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
    // Update the scene with delta time
    // For simplicity, use a fixed delta time
    static int lastTime = 0;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float dt = 0.0f;
    if (lastTime != 0) {
        dt = (currentTime - lastTime) / 1000.0f;  // Convert to seconds
    }
    lastTime = currentTime;
    
    scene.update(dt);
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
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callKeyboard(unsigned char key, int x, int y)
{
    if (instance)
    {
        instance->keyboard(key, x, y);
    }
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callIdle()
{
    if (instance)
    {
        instance->idle();
    }   
    else 
    {
        printf("ERROR: App instance is null\n");
    } 
}

void App::callDisplay()
{
    if (instance)
    {
        instance->display();
    }
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callMouseButton(int button, int state, int x, int y)
{
    if (instance)
    {
        instance->mouseButton(button, state, x, y);
    }    
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callMouseMotion(int x, int y)
{
    if (instance)
    {
        instance->mouseMotion(x, y);
    }
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callLaunchProjectile(float launchVX, float launchVY, float distance)
{
    if (instance) {
        instance->scene.launchProjectile(launchVX, launchVY, distance);
    } 
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}
