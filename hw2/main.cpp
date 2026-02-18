#include <random>



#define GL_SILENCE_DEPRECATION


#include "architecture/controller.h"
#include "architecture/model.h"
#include "architecture/view.h"


// global variables for storage:
Model m;
View v(m);
Controller c(m, v);


// DUE: Friday 02/20/2026 at 11:59pm
// The goal of this programming assignment is to give students experience with user
// interaction and OpenGL callback functions. Your task is to create an interactive
// game of your own design where Pac Man flies around in space eating food while
// being chased by space monsters. Your detailed requirements are listed below.

// A) Create simple geometric models for Pac Man, food, and one or more monsters
// out of 2D polygons. You are welcome to use any colors and shapes you like for
// the food and monsters, but Pac Man should be the traditional yellow disk with an
// open mouth. Display your geometric models in random locations on the screen.

// B) Use the OpenGL idle or timer callbacks to animate the food and monsters so they
// move slowly across the screen with random starting directions. When the food
// and monster objects reach the edges of the display window you can either have
// them bounce off in the opposite direction or teleport to the opposite side and
// reappear. It might be fun to have the monsters change directions at random
// intervals so they are less predictable.

// C) Use the OpenGL keyboard and mouse callbacks to control the motion of Pac Man.
// Your goal is to be able to move the Pac Man in any direction (not just up, down,
// left, right) so they can chase and eat the food while avoiding the monsters. Try
// not to make the Pac Man too fast and powerful, so it is a challenge to eat the food
// and avoid the monsters.

// D) Your final task will be to implement the game logic that detects when Pac Man
// collides with food or one of the monsters. Once you have done this, you can add
// some sort of scoring scheme to the game. For example, Pac Man could gain
// points by eating food, and lose one of their lives if they collide with by one of the
// monsters. You can decide when the game ends based on your scoring scheme.

// For this project you ARE allowed to use generative AI to learn about OpenGL and to
// help you complete two of four tasks above. You are required to keep track of all of
// your AI prompts in a separate document to submit with your project report.

static float lastTime = 0.0f;

void init()  // initialize OPENGL
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

}


float getTimeSeconds() 
{
    return glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
}


// allows us to call display and keyboard calls smoothly

void displayCallback()
{
    v.display();
    glutSwapBuffers();
}

void keyUpCallback(unsigned char key, int x, int y)
{
    c.keyUp(key, x, y);
}
void keyDownCallback(unsigned char key, int x, int y)
{
    c.keyDown(key, x, y);
}



// now to control gsame timing with ticks

void timerCallback(int)
{
    float now = getTimeSeconds();
    float dt = now - lastTime;
    lastTime = now;

    m.update(dt);
    glutPostRedisplay();

    glutTimerFunc(16, timerCallback, 0); // ~60fps
}

void tick() {
    float now = getTimeSeconds();
    float dt = now - lastTime;
    lastTime = now;

    m.update(dt);
    v.display();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(250, 250);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Warren Roberts - Assignment 2 Pacman");


    glEnable(GL_DEPTH_TEST);
    init();


    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyDownCallback);
    glutKeyboardUpFunc(keyUpCallback);


    lastTime = getTimeSeconds();
    glutTimerFunc(16, timerCallback, 0);


    glutMainLoop();
    return 0;
}