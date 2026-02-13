# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -DGL_SILENCE_DEPRECATION

# Frameworks (macOS)
FRAMEWORKS = -framework OpenGL -framework GLUT

# Source files
SRC = main.cpp \
      components/polygon.cpp \
      components/vertex.cpp \
      entities/dot.cpp

# Output executable
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(FRAMEWORKS)

clean:
	rm -f $(TARGET)
