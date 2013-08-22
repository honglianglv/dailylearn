CC = g++ 
LIBS = -levent -lpthread ./libNLPIR.so 
CFLAGS = -m64 -O2 -DOS_LINUX
INCLUDE = 

all:httpSplitWord SplitWordForFile
http_server.o:http_server.h http_server.cpp
	$(CC) -c http_server.cpp $(CFLAGS) $(INCLUDE) 
httpSplitWord:http_split_word.cpp http_server.o header.h
	$(CC) http_split_word.cpp http_server.o $(CFLAGS) $(INCLUDE) $(LIBS) -o httpSplitWord
SplitWordForFile: SplitWordForFile.cpp header.h
	$(CC) SplitWordForFile.cpp $(CFLAGS) $(INCLUDE) $(LIBS) -o SplitWordForFile
clean:
	rm -f httpSplitWord
	rm -f *.o
