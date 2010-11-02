GXX=g++
CPPFLAGS=-c -Wall -I/usr/include/opencv/
ARGS= -Bstatic -lGLU -lGL -O3 -Wall -lIL -lhighgui   -Bshared -lglfw -larmadillo
SRC=GL_exart_function.cpp main.cpp file_handler.cpp mesh2d.cpp shader.cpp toolModule.cpp material.cpp image.cpp cv_camera_capture.cpp camera.cpp light.cpp graphicsCore.cpp scenegraph.cpp OBJLoader.cpp
OBJS=$(SRC:.cpp=.o)
%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS)
	$(GXX)  $(ARGS) $^ -o run 

clean:
	rm -f ./*.o run
