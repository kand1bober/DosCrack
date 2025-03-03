CC = g++
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:
	cp /home/vyacheslav/vzlom/src/CRACKME.com  /home/vyacheslav/vzlom/
	$(CC) keygen.cpp $(CFLAGS) -o keygen 

clean:
	rm keygen 
	