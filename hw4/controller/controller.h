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

#include "../view/camera.h"

#pragma once

class Controller
{
    public:
    // constructor
        Controller();

    // getters
        Camera getCamera() const;

        bool getZoomInPressed() const;
        bool getZoomOutPressed() const;

        bool getUpPressed() const;
        bool getDownPressed() const;
        bool getLeftPressed() const;
        bool getRightPressed() const;



    // setters   
        void setZoomInPressed(bool a);
        void setZoomOutPressed(bool a);
        void setUpPressed(bool a);
        void setDownPressed(bool a);
        void setLeftPressed(bool a);
        void setRightPressed(bool a);  


    // functionality
        void handleKeyDown(unsigned char key);
        void handleKeyUp(unsigned char key);
        void update();

    private:
        Camera camera;
        bool zoomInPressed;
        bool zoomOutPressed;

        bool upPressed;
        bool downPressed;
        bool leftPressed;
        bool rightPressed;

        float cameraMoveSpeed = 0.025f;
        float zoomIncrement = 0.05f;
};

