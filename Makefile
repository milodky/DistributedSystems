
# For compiling we do not need the -lssl option.
# -l option is only used for linking. It is required while building
compile:
	g++ -S server.cpp lsp.cpp
	g++ -S client.cpp lsp.cpp
	g++ -S worker.cpp

build:

	g++ -g -o server.o server.cpp lsp.cpp connection.cpp
	g++ -g -o client.o client.cpp lsp.cpp connection.cpp
	g++ -g -o worker.o worker.cpp -lssl

clean:
	rm -f *.o *.gch *.s server client worker
	
	