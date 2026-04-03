/******************************************************************************************
 *  File Name:      controller.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Declares input control methods used to respond to keyboard input
 *  and pass commands to the application.
 * 
 *  Dependencies:
 *  App and camera-related components
 * 
 *  Notes:
 *  Separates input logic from rendering logic.
 *
 ******************************************************************************************/

#pragma once

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cmath>
#include "../view/camera.h"


class Controller
{
    public:
    // constructor
        Controller();

    // getters
        const Camera& getCamera() const;

        // Movement state getters (used internally)
        bool getUpPressed() const;
        bool getDownPressed() const;
        bool getLeftPressed() const;
        bool getRightPressed() const;


    // functionality
        void handleKeyDown(unsigned char key);
        void handleKeyUp(unsigned char key);

        void mouseButton(int button, int state, int x, int y);
        void mouseMotion(int x, int y);

        void update();

    private:
        Camera camera;
        bool upPressed = false;
        bool downPressed = false;
        bool leftPressed = false;
        bool rightPressed = false;

        // These will be initialized in the constructor using Config values
        float cameraMoveSpeed;
        float zoomIncrement;
        float rotationSpeed;

        bool isDragging = false;

        float startX = 0.0f;
        float startY = 0.0f;
        float endX = 0.0f;
        float endY = 0.0f;
        float clickWorldX = 0.0f;
        float clickWorldY = 0.0f;

        float maxSpeed;

};

