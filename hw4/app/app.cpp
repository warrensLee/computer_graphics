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
    
    glOrtho(-zoom, zoom, -zoom, zoom, -50, 50);

    // switch to modelview matrix for scene rendering
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // apply camera translation based on camera position
    glTranslatef(-controller.getCamera().getCameraX(), -controller.getCamera().getCameraY(), -controller.getCamera().getCameraZ());
    
    // draw the scene
    renderer.draw(scene);

    // this is the line that the user drags
    // with their mouse, and the cannon ball
    // will follow behind it when released
    dragTrajectoryLine();

    // switch to 2D for text
    beginTextMode(width, height);

    // white text color
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // text positioning
    int textX = 20;
    int textY = height - 30;

    // text content and draw method
    drawText(textX, textY, "DRAG TO THROW BASKETBALL");

    endTextMode();

    glutSwapBuffers();
}

void App::dragTrajectoryLine()
{
    // draw trajectory line if dragging
    if (controller.getIsDragging()) 
    {
        float worldStartX, worldStartY, worldEndX, worldEndY;
        controller.getDragWorldCoordinates(worldStartX, worldStartY, worldEndX, worldEndY);
        renderer.drawTrajectoryLine(worldStartX, worldStartY, worldEndX, worldEndY);
    }

}

void App::drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);

    for (const char* c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void App::beginTextMode(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
}

void App::endTextMode()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
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
