/******************************************************************************************
 *  File Name:      app.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 22, 2026
 *
 *  Description:
 *  Implements the main application loop: initializes OpenGL, forwards GLUT
 *  callbacks to the RayTracer and Controller, and blits the ray-traced image.
 *
 *  Dependencies:
 *  app.h
 *
 *  Notes:
 *  Q/E zoom the ray tracer camera. WASD pans via the Controller.
 *
 ******************************************************************************************/

#include "app.h"

App* App::instance = nullptr;

App::App() : rayTracer(), renderer(), controller()
{
    instance = this;
}

void App::init()
{
    initOpenGL();
}

void App::initOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void App::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer.drawRayTracedImage(rayTracer.getImageBuffer(), Config::XDIM, Config::YDIM);
    glutSwapBuffers();
}

void App::keyboard(unsigned char key, int x, int y)
{
    (void)x; (void)y;

    controller.handleKeyDown(key);

    // Q/E zooms the camera distance
    if (key == 'e') 
        rayTracer.increaseCameraDistance();
    if (key == 'q') 
        rayTracer.decreaseCameraDistance();

    glutPostRedisplay();
}

void App::keyboardKeyUp(unsigned char key, int x, int y)
{
    (void)x; (void)y;
    controller.handleKeyUp(key);
}

void App::idle()
{
    static int lastTime = 0;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float dt = 0.0f;

    if (lastTime != 0)
        dt = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    controller.update(dt);
    rayTracer.updateScene(dt);
    rayTracer.traceScene();
    glutPostRedisplay();
}

void App::callDisplay()
{
    if (instance) 
        instance->display();
    else 
        printf("ERROR: App instance is null\n");
}

void App::callKeyboard(unsigned char key, int x, int y)
{
    if (instance) 
        instance->keyboard(key, x, y);
    else 
        printf("ERROR: App instance is null\n");
}

void App::callKeyboardKeyUp(unsigned char key, int x, int y)
{
    if (instance) 
        instance->keyboardKeyUp(key, x, y);
    else 
        printf("ERROR: App instance is null\n");
}

void App::callIdle()
{
    if (instance) 
        instance->idle();
    else 
        printf("ERROR: App instance is null\n");
}
