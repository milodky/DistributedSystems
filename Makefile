
LIBS = -lprotobuf-c -lpthread -lssl

SRC = lsp.cpp connection.cpp functions.cpp lspmessage.pb-c.c

# For compiling we do not need the -lssl option.
# -l option is only used for linking. It is required while building
compile:
	g++ -S server.cpp $(SRC)
	g++ -S client.cpp $(SRC)
	g++ -S worker.cpp

# -lpthread -> includes the pthread library for linking
build:
	g++ -g -o server server.cpp $(SRC) $(LIBS)
	g++ -g -o client client.cpp $(SRC) $(LIBS)
	g++ -g -o worker worker.cpp $(LIBS)

clean:
	rm -f *.o *.gch *.s server client worker
	
	