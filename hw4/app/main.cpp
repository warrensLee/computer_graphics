/******************************************************************************************
 *  File Name:      main.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Entry point of the program. Creates the application object and starts
 *  the OpenGL execution loop.
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
    glutInit(&argc, argv);                         // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Double buffer, RGB
    glutInitWindowSize(800, 600);                  // Window size
    glutCreateWindow("Computer Graphics: Homework 3, Terrain Generation on a Grid");       // Window title


    App app;
    app.init();
    app.initOpenGL();


    glutDisplayFunc(app.callDisplay);
    glutKeyboardFunc(app.callKeyboard);
    glutKeyboardUpFunc(app.callKeyboardKeyUp);
    
    glutIdleFunc(app.callIdle);

    glutMainLoop();                                // Start event loop
    return 0;
}