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


class Camera
{
    public:
    // constructors
        Camera() = default;
         
                
    // getters
        float getCameraX() const;
        float getCameraY() const;
        float getCurrentZoom() const;

    
    // setters
        void setCameraX(float x);
        void setCameraY(float y);
        void setCurrentZoom(float z);


    // functionality

    private:
    // zoom 
        float currentZoom = 4.0f;       //starting zoom

    // camera
        float xCameraPosition = 0.0f;
        float yCameraPosition = 0.5f;


};