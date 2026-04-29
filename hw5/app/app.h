/******************************************************************************************
 *  File Name:      app.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 29, 2026
 *
 *  Description:
 *  Declares the App class: GLUT callbacks, input forwarding, and the
 *  top-level objects (RayTracer, Render, Controller).
 *
 *  Dependencies:
 *  raytracer.h, render.h, controller.h, config.h
 *
 *  Notes:
 *  Singleton pattern bridges GLUT C-style callbacks to C++ instance methods.
 *  Added handlers for apple or windows OpenGL includes.
 *
 ******************************************************************************************/

#pragma once

// #include <OpenGL/gl.h>
// #include <GLUT/glut.h>
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif
#include <stdio.h>

#include "../core/config.h"
#include "../controller/controller.h"
#include "../view/render.h"
#include "../model/raytracer.h"

class App
{
public:
    App();
    void init();
    void initOpenGL();
    void display();
    void keyboard(unsigned char key, int x, int y);
    void keyboardKeyUp(unsigned char key, int x, int y);
    void idle();

    static void callDisplay();
    static void callKeyboard(unsigned char key, int x, int y);
    static void callKeyboardKeyUp(unsigned char key, int x, int y);
    static void callIdle();

private:
    static App* instance;
    RayTracer  rayTracer;
    Render     renderer;
    Controller controller;
};
