#include "polygon.h"
#include <random>

// Implement a C++ program that declares and initializes a vector of P polygons
// that have random (x,y,z) point coordinates between [-1..1] and random color
// values between [0..1]. To verify/debug this code, you should loop over this
// vector and call “display” for each polygon. This should print the random polygon
// values

std::vector<Polygon> polygons;

float theta = 0.0f;

std::vector<Polygon> testPolygons(int n, int m)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> position(-1.0f, 1.0f);
    std::uniform_real_distribution<float> color(0.0f, 1.0f);

    std::vector<Polygon> polys;
    polys.reserve(m);

    for (int polyIdx = 0; polyIdx < m; polyIdx++)
    {
        std::vector<Vertex> verts;
        verts.reserve(n);

        for (int vertIdx = 0; vertIdx < n; vertIdx++)
        {
            Vertex v(position(gen), position(gen), position(gen), color(gen), color(gen), color(gen));
            verts.push_back(v);
        }

        polys.emplace_back(verts);
    }

    return polys;
}

// std::vector<Polygon> testPolygons(int n, int m)
// {
//     std::random_device rd;  // random number from hardware for position
//     std::mt19937 gen(rd()); // seed the genrator

//     // now to actually set the range of "randomness"
//     std::uniform_real_distribution<float> position(-1.0f, 1.0f);
//     std::uniform_real_distribution<float> color(0.0f, 1.0f);

//     std::vector<Vertex> verts;
//     std::vector<Polygon> polys;

//     for (int i = 0; i < m; i++)
//     {
//         for (int i = 0; i < n; i++)
//         {
//             Vertex v(position(gen), position(gen), position(gen), color(gen), color(gen), color(gen));
//             verts.push_back(v);
//         }
//         Polygon p(verts);
//         polys.push_back(p);
//     }

//     return polys;
// }

void allInformation(std::vector<Polygon> polys)
{
    int count = 1;           // track what vertex we are on
    for (Polygon &p : polys) // iterate thru each polygon in the vector
    {
        std::cout << "Polygon (" << count << "):" << std::endl; // output the specific polygon we are at
        p.polygonInformation();                                 // print that polygon's information
        count++;
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void display()
{
    // Incrementally rotate objects
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(theta, 0.0, 1.0, 0.0);
    theta += 1.0f;
    for (Polygon &p : polygons) // iterate thru each polygon in the vector of polygons
    {
        p.display();
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (h == 0) ? 1.0f : (float)w / (float)h;

    if (aspect >= 1.0f)
        glOrtho(-aspect, aspect, -1, 1, -1, 1);
    else
        glOrtho(-1, 1, -1/aspect, 1/aspect, -1, 1);

    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}



int main(int argc, char *argv[])
{
    polygons = testPolygons(4, 5);          // sides, polygons
    // allInformation(polygons);
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(250, 250);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Warren Roberts - Assignment 1");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
}