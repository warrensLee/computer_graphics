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
        float currentZoom;       //starting zoom

    // camera position
        float xCameraPosition;
        float yCameraPosition;
        float zCameraPosition;
        
    // camera rotation (in degrees)
        float yaw;      // rotation around Y axis (left/right)
        float pitch;    // rotation around X axis (up/down)
        float roll;     // rotation around Z axis (tilt)

};
