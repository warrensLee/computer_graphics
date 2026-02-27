CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -DGL_SILENCE_DEPRECATION
LDFLAGS  = -framework OpenGL -framework GLUT

TARGET = main

OBJS = app/main.o app/app.o app/callbacks.o \
       core/math.o core/random.o \
       model/world.o model/terrainSystem.o \
       view/render.o view/camera.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)