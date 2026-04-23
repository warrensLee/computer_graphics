/******************************************************************************************
 *  File Name:      main.cpp
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 22, 2026
 *
 *  Description:
 *  Entry point. Initializes GLUT and starts the ray tracer application loop.
 *
 *  Dependencies:
 *  app.h
 *
 *  Notes:
 *  Contains only startup logic.
 *
 ******************************************************************************************/

#include "app.h"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Config::XDIM, Config::YDIM);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("Computer Graphics: Homework 5, Ray Tracer");

    App app;
    app.init();

    glutDisplayFunc(app.callDisplay);
    glutKeyboardFunc(app.callKeyboard);
    glutKeyboardUpFunc(app.callKeyboardKeyUp);
    glutIdleFunc(app.callIdle);

    glutMainLoop();
    return 0;
}
