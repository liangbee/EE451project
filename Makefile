CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

serial : serial.cpp
	g++ serial.cpp -o bin/serial $(CFLAGS) $(LIBS)
clean:
	rm bin/serial