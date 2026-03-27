# *****************************************************************************************
# *  File Name:      Makefile
# *  Author:         Warren Roberts
# *  Created:        February 26, 2026
# *  Last Modified:  March 28, 2026
# *
# *  Description:
# *  Builds the terrain generation and rendering project, including compilation,
# *  linking, and cleanup targets.
# *
# *  Dependencies:
# *  All project source and header files
# *
# *  Notes:
# *  Used to simplify compiling and rebuilding the full project.
# *
# *****************************************************************************************

CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -DGL_SILENCE_DEPRECATION
LDFLAGS  = -framework OpenGL -framework GLUT

TARGET = main

OBJS = app/main.o app/app.o \
       core/math.o core/imageLoader.o \
       model/mesh.o model/texture.o model/scene.o model/3DObject.o \
	   controller/controller.o \
       view/render.o view/camera.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)