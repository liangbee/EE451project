CFLAGS = `pkg-config --cflags --libs opencv`
LIBS = `pkg-config --libs opencv`

all: serial cuda pthreads
serial : serial/serial.cpp
	g++ serial/serial.cpp -o bin/serial $(CFLAGS) $(LIBS)
cuda : parallel/parallel.cu
	nvcc parallel/parallel.cu -o bin/parallel_cuda -std=c++11 `pkg-config --cflags --libs opencv`
pthreads : pthreads.c
	gcc pthreads.c -g -Wall -Wextra -o bin/pthreads 
clean:
	rm -r bin
	mkdir bin
