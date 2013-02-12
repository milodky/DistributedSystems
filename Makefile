
LIBS = -lprotobuf-c -lpthread -lssl

SRC = lsp.cpp connection.cpp functions.cpp lspmessage.pb-c.c \
	connectionInfo.cpp serializer.cpp MessageReceiver.cpp \
	MessageProcessor.cpp inbox.cpp MessageSender.cpp \
	lsppacket.cpp

# For compiling we do not need the -lssl option.
# -l option is only used for linking. It is required while building
compile:
	g++ -S server.cpp $(SRC)
	g++ -S client.cpp $(SRC)
	g++ -S worker.cpp $(SRC)

# -lpthread -> includes the pthread library for linking
build:

	g++ -g -o server server.cpp $(SRC) $(LIBS)
	g++ -g -o request client.cpp $(SRC) $(LIBS)
	g++ -g -o worker worker.cpp $(SRC) $(LIBS)

clean:
	rm -f *.o *.gch *.s server request worker client
	
	