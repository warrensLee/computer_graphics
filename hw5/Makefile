# *****************************************************************************************
# *  File Name:      Makefile
# *  Author:         Warren Roberts
# *  Created:        March 26, 2026
# *  Last Modified:  April 29, 2026
# *
# *  Description:
# *  Builds the ray tracing project. Updated to handle both Windows and macOS OpenGL linking.
# *
# *****************************************************************************************

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    CXX = clang++
    CXXFLAGS += -DGL_SILENCE_DEPRECATION
    LDFLAGS = -framework OpenGL -framework GLUT
else
    LDFLAGS = -lGL -lGLU -lglut
endif

TARGET = main

OBJS = app/main.o app/app.o \
       core/ray_classes.o \
       model/raytracer.o model/object3D.o model/scene.o model/cubeObject.o model/sphereObject.o model/plane3D.o \
       controller/controller.o \
       view/render.o view/camera.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

# CXX      = clang++
# CXXFLAGS = -std=c++17 -Wall -Wextra -I. -DGL_SILENCE_DEPRECATION
# LDFLAGS  = -framework OpenGL -framework GLUT

# TARGET = main

# OBJS = app/main.o app/app.o \
#        core/ray_classes.o \
#        model/raytracer.o model/object3D.o model/scene.o model/cubeObject.o model/sphereObject.o model/plane3D.o \
#        controller/controller.o \
#        view/render.o view/camera.o

# all: $(TARGET)

# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJS) $(TARGET)

# .PHONY: all clean
