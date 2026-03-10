/******************************************************************************************
 *  File Name:      controller.h
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

#pragma once

class Controller
{
    public:
    // constructor
        Controller() = default;

    // getters
        bool getZoomInPressed() const;
        bool getZoomOutPressed() const;
        float getCurrentZoom() const;
        bool getUpPressed() const;
        bool getDownPressed() const;
        bool getLeftPressed() const;
        bool getRightPressed() const;
        float getCameraX() const;
        float getCameraY() const;


    // setters   
        void setZoomInPressed(bool a);
        void setZoomOutPressed(bool a);
        void setUpPressed(bool a);
        void setDownPressed(bool a);
        void setLeftPressed(bool a);
        void setRightPressed(bool a);
        void setCameraX(float x);
        void setCameraY(float y);

    // functionality
        void handleKeyDown(unsigned char key);
        void handleKeyUp(unsigned char key);
        void update();

    private:
        bool zoomInPressed;
        bool zoomOutPressed;

        bool upPressed;
        bool downPressed;
        bool leftPressed;
        bool rightPressed;

        float zoomIncrement = 0.05f;
        float currentZoom = 3.0f;       //starting zoom

        float xCameraPosition = 0.0f;
        float yCameraPosition = 0.5f;
        float cameraMoveSpeed = 0.025f;
};

