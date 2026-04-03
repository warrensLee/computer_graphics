/******************************************************************************************
 *  File Name:      app.cpp
 *  Author:         Warren Roberts
 *  Created:        February 26, 2026
 *  Last Modified:  April 3, 2026
 *
 *  Description:
 *  implements the main application flow, including initialization of terrain,
 *  camera, rendering systems, and OpenGL state setup.
 * 
 *  Dependencies:
 *  app.h
 * 
 *  Notes:
 *  coordinates startup behavior before entering the render loop.
 *
 ******************************************************************************************/


#include "app.h"
#include "../controller/controller.h"
#include <string>


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
    
    // No rotation for simplicity - camera looks straight ahead

    // draw the scene
    renderer.draw(scene);
    
    // Draw trajectory line if dragging
    if (controller.getIsDragging()) {
        float worldStartX, worldStartY, worldEndX, worldEndY;
        controller.getDragWorldCoordinates(worldStartX, worldStartY, worldEndX, worldEndY);
        renderer.drawTrajectoryLine(worldStartX, worldStartY, worldEndX, worldEndY);
    }

    // Render text instructions at the top of the screen
    // Save current projection matrix
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    // Set up orthographic projection matching window dimensions
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    gluOrtho2D(0, width, 0, height);
    
    // Switch to modelview matrix for text rendering
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Disable depth testing for text
    glDisable(GL_DEPTH_TEST);
    
    // Set text color to white
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Position text at the top center
    std::string text = "A/D to move right and left and click and drag to launch cannon ball";
    int textWidth = 0;
    for (char c : text) {
        textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    int x = (width - textWidth) / 2;
    int y = height - 20; // 20 pixels from top
    
    // Render each character
    glRasterPos2i(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // Restore OpenGL state
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    
    // Restore projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
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

void App::idle()
{
    // update controller state (movement, rotation)
    controller.update();
    
    // calculate delta time for smooth animation
    static int lastTime = 0;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float dt = 0.0f;

    if (lastTime != 0) 
        dt = (currentTime - lastTime) / 1000.0f;  // convert to seconds
    
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
