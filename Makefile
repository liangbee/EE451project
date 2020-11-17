CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

serial : serial.cpp
	g++ serial.cpp -o bin/serial $(CFLAGS) $(LIBS)
cuda : parallel/parallel.cu
	nvcc parallel/parallel.cu -o bin/parallel_cuda $(CFLAGS) $(LIBS)
clean:
	rm bin/serial bin/parallel_cuda