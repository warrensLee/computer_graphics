/******************************************************************************************
 *  File Name:      app.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  March 10, 2026
 *
 *  Description:
 *  implements the main application flow, including initialization of terrain,
 *  camera, rendering systems, and OpenGL state setup.
 * 
 *  Dependencies:
 *  app.h and all linked subsystems
 * 
 *  Notes:
 *  coordinates startup behavior before entering the render loop.
 *
 ******************************************************************************************/


#include "app.h"


//********************** initialization **********************//

App* App::instance = nullptr;

App::App() : renderer(), controller(), scene()
{
    instance = this;
}

void App::init()
{
    initOpenGL();
    renderer.init();
}

void App::initOpenGL()
{
    // set black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // enable depth testing for 3D
    glEnable(GL_DEPTH_TEST);
}


//********************** Functionality **********************//

void App::display()
{
    // get window size for aspect ratio
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    
    float zoom = controller.getCamera().getCurrentZoom();
    
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // calculate aspect ratio
    float aspect = (float)width / (float)height;
    
    // near and far clipping planes
    float near = 0.1f;
    float far = 50.0f;
    
    // adjust orthographic bounds based on zoom and aspect ratio
    float right = zoom * aspect;
    float left = -right;
    float top = zoom;
    float bottom = -top;
    
    glOrtho(left, right, bottom, top, near, far);

    // switch to modelview matrix for scene rendering
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // apply camera translation based on camera position
    // camera is at (x, y, z) looking along -Z axis
    glTranslatef(-controller.getCamera().getCameraX(), 
                 -controller.getCamera().getCameraY(), 
                 -controller.getCamera().getCameraZ());  // move scene opposite to camera position
    
    // Rotate camera to look slightly downward to see the ground
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);  // pitch down 30 degrees

    // draw the scene
    renderer.draw(scene);

    // swap buffers for smooth animation
    glutSwapBuffers();
}




void App::keyboard(unsigned char key, int x, int y)
{
    // unused vars
    (void) x;
    (void) y;
    controller.handleKeyDown(key);
    glutPostRedisplay();

}

void App::keyboardKeyUp(unsigned char key, int x, int y)
{
    // unused vars
    (void) x;
    (void) y;
    controller.handleKeyUp(key);
}

void App::specialKey(int key, int x, int y)
{
    (void) x;
    (void) y;
    controller.handleSpecialKeyDown(key);
    glutPostRedisplay();
}

void App::specialKeyUp(int key, int x, int y)
{
    (void) x;
    (void) y;
    controller.handleSpecialKeyUp(key);
}

void App::idle()
{
    // update controller state (movement, rotation)
    controller.update();
    
    // calculate delta time for smooth animation
    static int lastTime = 0;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float dt = 0.0f;
    if (lastTime != 0) {
        dt = (currentTime - lastTime) / 1000.0f;  // convert to seconds
    }
    lastTime = currentTime;
    
    // update scene objects
    scene.update(dt);
    
    // request redisplay
    glutPostRedisplay();
}

void App::mouseButton(int button, int state, int x, int y)
{
    controller.mouseButton(button, state, x, y);
}

void App::mouseMotion(int x, int y)
{
    controller.mouseMotion(x, y);
}


//********************** Callbacks **********************//

void App::callKeyboardKeyUp(unsigned char key, int x, int y)
{
    if (instance)
    {
        instance->keyboardKeyUp(key, x, y);
    }
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callKeyboard(unsigned char key, int x, int y)
{
    if (instance)
    {
        instance->keyboard(key, x, y);
    }
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callSpecialKey(int key, int x, int y)
{
    if (instance)
    {
        instance->specialKey(key, x, y);
    }
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callSpecialKeyUp(int key, int x, int y)
{
    if (instance)
    {
        instance->specialKeyUp(key, x, y);
    }
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callIdle()
{
    if (instance)
    {
        instance->idle();
    }   
    else 
    {
        printf("ERROR: App instance is null\n");
    } 
}

void App::callDisplay()
{
    if (instance)
    {
        instance->display();
    }
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callMouseButton(int button, int state, int x, int y)
{
    if (instance)
    {
        instance->mouseButton(button, state, x, y);
    }    
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callMouseMotion(int x, int y)
{
    if (instance)
    {
        instance->mouseMotion(x, y);
    }
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}

void App::callLaunchProjectile(float launchVX, float launchVY, float distance, float spawnX, float spawnY)
{
    if (instance) {
        instance->scene.launchProjectile(launchVX, launchVY, distance, spawnX, spawnY);
    } 
    else 
    {
        printf("ERROR: App instance is null\n");
    }
}
