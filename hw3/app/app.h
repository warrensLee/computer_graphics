/******************************************************************************************
 *  File Name:      app.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  February 26, 2026
 *
 *  Description:
 *  Defintion of commonly used math tools such as clamping, length, minimum, etc.
 * 
 *  Dependencies:
 *
 *  Notes:
 *
 ******************************************************************************************/
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdio.h>

#include "../core/config.h"
#include "../controller/controller.h"
#include "../view/render.h"
#include "../terrain/height.h"



#pragma once

class App
{
    public: 
        App();
        void init();



        void initOpenGL();
        void display();
        void reshape(int w, int h);
        void keyboard(unsigned char key, int x, int y);
        void idle();
        static void callDisplay();
        static void callreshape(int w, int h);
        static void callKeyboard(unsigned char key, int x, int y);
        static void callIdle();
        
    private:
        static App* instance;
        Height height;
        Render renderer;
        Controller controller;

};