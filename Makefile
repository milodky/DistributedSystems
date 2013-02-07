compile:
	g++ -S *.cpp

build:

	g++ -g -o server.o server.cpp lsp.cpp
	g++ -g -o client.o client.cpp lsp.cpp
	g++ -g -o worker.o worker.cpp -lssl

clean:
	rm -f *.o *.gch *.s server client worker
	
	