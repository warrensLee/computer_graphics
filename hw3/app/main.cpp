/******************************************************************************************
 *  File Name:      main.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  February 26, 2026
 *
 *  Description:
 *  Defintion of commonly used math tools such as clamping, length, minimum, etc.
 * 
 *  Dependencies:
 *  app, callbacks
 * 
 *  Notes:
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