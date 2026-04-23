# *****************************************************************************************
# *  File Name:      Makefile
# *  Author:         Warren Roberts
# *  Created:        March 26, 2026
# *  Last Modified:  April 22, 2026
# *
# *  Description:
# *  Builds the ray tracing project.
# *
# *****************************************************************************************

CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -DGL_SILENCE_DEPRECATION
LDFLAGS  = -framework OpenGL -framework GLUT

TARGET = main

OBJS = app/main.o app/app.o \
       core/ray_classes.o \
       model/raytracer.o \
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
