compile:
	g++ -S *.cpp -lssl

build:

	g++ -g -o server.o server.cpp
	g++ -g -o client.o client.cpp
	g++ -g -o worker.o worker.cpp -lssl

clean:
	rm -f *.o *.gch *.s server client worker
	
	