#pragma once

#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <GLUT/glut.h>
#elif defined(_WIN32)
  #include <windows.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
  // pick ONE of these depending on what you installed:
  //#include <GL/freeglut.h>   // MSYS2/FreeGLUT (recommended)
  // #include <GL/glut.h>     // older GLUT
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include <GL/freeglut.h>
#endif
