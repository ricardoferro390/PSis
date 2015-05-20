CC = gcc
CFLAGS = -Wall -ansi

PBC = protoc-c
PBCFLAGS = --c_out=.

all:
	$(PBC) $(PBCFLAGS) ProtoBuffers.proto
	$(CC) $(CFLAGS) server.c ProtoBuffers.pb-c.c -l protobuf-c -o server
	$(CC) $(CFLAGS) client.c ProtoBuffers.pb-c.c -l protobuf-c -o client
	
ProtoBuffers.pb-c.c:
	$(PBC) $(PBCFLAGS) ProtoBuffers.proto

server: ProtoBuffers.pb-c.c
	$(CC) $(CFLAGS) server.c ProtoBuffers.pb-c.c -l protobuf-c -o server 

client: ProtoBuffers.pb-c.c
	$(CC) $(CFLAGS) client.c ProtoBuffers.pb-c.c -l protobuf-c -o client 
