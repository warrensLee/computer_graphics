/******************************************************************************************
 *  File Name:      controller.h
 *  Author:         Warren Roberts
 *  Created:        March 26, 2026
 *  Last Modified:  April 22, 2026
 *
 *  Description:
 *  Declares keyboard input handling and camera movement for the ray tracer.
 *
 *  Dependencies:
 *  camera.h, config.h
 *
 *  Notes:
 *  WASD moves the camera; Q/E zoom is handled directly in App.
 *
 ******************************************************************************************/

#pragma once

#include "../view/camera.h"
#include "../core/config.h"

class Controller
{
public:
    Controller();

    const Camera& getCamera() const;

    void handleKeyDown(unsigned char key);
    void handleKeyUp(unsigned char key);
    void update(float dt);

private:
    Camera camera;
    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;
};
