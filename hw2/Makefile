CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra

TARGET = main

SRC = main.cpp \
      components/polygon.cpp \
      components/vertex.cpp \
      entities/dot.cpp \
	  entities/ghost.cpp \
	  entities/pacman.cpp \
	  entities/entity.cpp \
	  architecture/controller.cpp \
	  architecture/view.cpp \
	  architecture/model.cpp

UNAME_S := $(shell uname -s 2>/dev/null)

LIBS =
INCLUDES =

ifeq ($(UNAME_S),Darwin)
	CXXFLAGS += -DGL_SILENCE_DEPRECATION
	LIBS += -framework OpenGL -framework GLUT
endif

# Linux / WSL
ifeq ($(UNAME_S),Linux)
	LIBS += -lGL -lGLU -lglut
	# If your distro uses freeglut, this may be needed instead:
	# LIBS += -lGL -lGLU -lfreeglut
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $@ $(LIBS)

clean:
	rm -f main main.exe
