CC = g++
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:
	
	$(CC) keygen.cpp $(CFLAGS) -o keygen 

clean:
	rm keygen 
	