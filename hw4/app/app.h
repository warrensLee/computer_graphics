/******************************************************************************************
 *  File Name:      app.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Declares the App class responsible for managing application-level setup,
 *  display callbacks, and integration between terrain generation and rendering.
 * 
 *  Dependencies:
 *  Terrain, view, and controller components
 * 
 *  Notes:
 *  Acts as the main connection point for the project.
 *
 ******************************************************************************************/


#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdio.h>

#include "../core/config.h"
#include "../controller/controller.h"
#include "../view/render.h"

#pragma once

class App
{
    public: 
    // constructors
        App();
        void init();


    // OpenGL methods
        void initOpenGL();
        void display();
        void reshape(int w, int h);
        void keyboard(unsigned char key, int x, int y);
        void keyboardKeyUp(unsigned char key, int x, int y);
        void idle();


    // callers to OpenGL methods
        static void callDisplay();
        static void callreshape(int w, int h);
        static void callKeyboard(unsigned char key, int x, int y);
        static void callKeyboardKeyUp(unsigned char key, int x, int y);
        static void callIdle();

        
    private:
    // method members
        static App* instance;
        Render renderer;
        Controller controller;
        Scene scene;

};