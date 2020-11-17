CFLAGS = `pkg-config --cflags --libs opencv`
LIBS = `pkg-config --libs opencv`

all: serial cuda 
serial : serial/serial.cpp
	g++ serial/serial.cpp -o bin/serial $(CFLAGS) $(LIBS)
cuda : cuda/parallel.cu
	nvcc cuda/parallel.cu -o bin/parallel_cuda -std=c++11 `pkg-config --cflags --libs opencv`
clean:
	rm -r bin
	mkdir bin
