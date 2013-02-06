compile:
	g++ -S *.cpp -lssl

build:

	g++ -g -o server server.cpp
	g++ -g -o client client.cpp
	g++ -g -o worker worker.cpp -lssl

clean:
	rm -f *.o *.gch *.s server client worker
	
	