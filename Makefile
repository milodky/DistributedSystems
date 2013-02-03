compile:
	g++ -S *.cpp

build:
	g++ -g -o server server.cpp
	g++ -g -o client client.cpp

clean:
	rm -f *.o *.gch *.s server client
	
	