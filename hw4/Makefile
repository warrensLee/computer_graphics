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
# *****************************************************************************************

CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -DGL_SILENCE_DEPRECATION
LDFLAGS  = -framework OpenGL -framework GLUT
LIBS     = core/libim/libim.a core/jpeg/libjpeg.a

TARGET = main

OBJS = app/main.o app/app.o \
       core/math.o core/imageLoader.o \
       model/texture.o model/scene.o model/object3D.o model/sphereObject.o model/cubeObject.o \
       controller/controller.o \
       view/render.o view/camera.o

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

core/jpeg/libjpeg.a:
	cd core/jpeg && make

core/libim/libim.a:
	cd core/libim && make

clean:
	rm -f $(OBJS) $(TARGET)
	cd core/jpeg && make clean || true
	cd core/libim && make clean || true