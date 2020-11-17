CC = g++
CPPFLAGS = -std=c++11
EXE  = bin/serial
DEPS = 
CFLAGS = `pkg-config --cflags opencv`
LDFLAGS = `pkg-config --libs opencv`

%.o: %.c $(DEPS)
	$(CC) $(CPPFLAGS) -c -o $@ $< $(CFLAGS) $(LDFAGS)

$(EXE): $(OBJ)
	$(CC) $(CPPFLAGS) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm $(EXE)