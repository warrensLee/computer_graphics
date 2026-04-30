/******************************************************************************************
 *  File Name:      camera.h
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  April 3, 2026
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
        void rotateYaw(float d);
        void rotatePitch(float d);
        void rotateRoll(float d);

    // ray tracer camera distance (zoom in/out)
        float getCameraDistance() const;
        void  increaseCameraDistance();
        void  decreaseCameraDistance();

    private:
    // zoom 
        float currentZoom;  

    // camera position
        float xCameraPosition;
        float yCameraPosition;    
        float zCameraPosition;  
        
    // camera rotation
        float yaw;      // rotation around Y axis (left/right)
        float pitch;    // rotation around X axis (up/down)
        float roll;     // rotation around Z axis (tilt)

    // ray tracer zoom distance
        float cameraDistance;

};
