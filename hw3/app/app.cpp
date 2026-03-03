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

void App::init()
{
    instance = this;
}

void App::initOpenGL()
{
    glClearColor(0.0, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

void App::display()
{
    printf("display called\n");
    glClear(GL_COLOR_BUFFER_BIT);      // Clear the screen

    glColor3f(1.0f, 0.0f, 0.0f);       // Set draw color (red)

    glBegin(GL_TRIANGLES);             // Start drawing
        glVertex2f(0.0f, 0.5f);        // Top
        glVertex2f(-0.5f, -0.5f);      // Bottom left
        glVertex2f(0.5f, -0.5f);       // Bottom right
    glEnd();

    glutSwapBuffers();                 // Render immediately
}

void App::reshape(int w, int h)
{

}

void App::keyboard(unsigned char key, int x, int y)
{

}

void App::idle()
{

}

void App::callDisplay()
{
    if (instance)
        instance->display();
}