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

    // setters   
        void setZoomInPressed(bool a);
        void setZoomOutPressed(bool a);

    // functionality
        void handleKey(unsigned char key);

    private:
        bool zoomInPressed;
        bool zoomOutPressed;
        float zoomIncrement = 0.05f;
        float currentZoom = 2.0f;       //starting zoom
};

