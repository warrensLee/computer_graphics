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


#pragma once

class App
{
    public: 
        App() = default;

        void initOpenGL();
        void display();
        void reshape(int w, int h);
        void keyboard(unsigned char key, int x, int y);
        void idle();
        
    private:
        void callDisplay();
        void callreshape(int w, int h);
        void callKeyboard(unsigned char key, int x, int y);
        void callIdle();
};