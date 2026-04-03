/******************************************************************************************
 *  File Name:      camera.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  Declares camera position and viewing controls for scene navigation.
 * 
 *  Dependencies:
 *  none
 * 
 *  Notes:
 *  Used by rendering and controller systems.
 *
 ******************************************************************************************/
#pragma once

class Camera
{
    public:
    // constructors
        Camera();
         
                
    // getters
        float getCameraX() const;
        float getCameraY() const;
        float getCameraZ() const;
        float getCurrentZoom() const;
        float getYaw() const;
        float getPitch() const;
        float getRoll() const;
    
    // setters
        void setCameraX(float x);
        void setCameraY(float y);
        void setCameraZ(float z);
        void setCurrentZoom(float z);
        void setYaw(float yaw);
        void setPitch(float pitch);
        void setRoll(float roll);
        void rotateYaw(float delta);
        void rotatePitch(float delta);
        void rotateRoll(float delta);

    // functionality

    private:
    // zoom 
        float currentZoom = 8.0f;       // starting zoom (smaller = more zoomed in)

    // camera position - slightly higher to see ground better
        float xCameraPosition = 0.0f;
        float yCameraPosition = 2.0f;    // slightly higher to see ground and objects
        float zCameraPosition = 10.0f;   // back from the scene
        
    // camera rotation - looking straight ahead
        float yaw = 0.0f;      // rotation around Y axis (left/right)
        float pitch = 0.0f;    // rotation around X axis (up/down) - 0 = horizontal
        float roll = 0.0f;     // rotation around Z axis (tilt)

};
