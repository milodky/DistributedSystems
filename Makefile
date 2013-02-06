compile:
	g++ -S *.cpp

build:
	g++ -g -o server server.cpp lsp.cpp
	g++ -g -o client client.cpp lsp.cpp

clean:
	rm -f *.o *.gch *.s server client
	
	