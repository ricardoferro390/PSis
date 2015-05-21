CC = gcc

PBC = protoc-c
PBCFLAGS = --c_out=.

all:
	$(PBC) $(PBCFLAGS) ProtoBuffers.proto
	$(CC) -c -o login_list.o login_list.c 
	$(CC) server.c login_list.c ProtoBuffers.pb-c.c -l protobuf-c -o server
	$(CC) client.c ProtoBuffers.pb-c.c -l protobuf-c -o client
	
ProtoBuffers.pb-c.c:
	$(PBC) $(PBCFLAGS) ProtoBuffers.proto

login_list.o:
	$(CC) -c -o login_list.o login_list.c
 
server: ProtoBuffers.pb-c.c login_list.o
	$(CC) server.c login_list.c ProtoBuffers.pb-c.c -l protobuf-c -o server.o
	$(CC) -c -o server server.o login_list.o

client: ProtoBuffers.pb-c.c
	$(CC) client.c ProtoBuffers.pb-c.c -l protobuf-c -o client 
