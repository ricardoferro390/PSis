CC = gcc
PBC = protoc-c
PBCFLAGS = --c_out=.
PTHREADS = -lpthread

all:
	$(CC) -c -o login_list.o login_list.c -g
	$(CC) server.c login_list.c ProtoBuffers.pb-c.c message.c -l protobuf-c -o server $(PTHREADS) -g
	$(CC) client.c message.c ProtoBuffers.pb-c.c -l protobuf-c -o client -g $(PTHREADS)
	$(CC) admin.c message.c ProtoBuffers.pb-c.c -l protobuf-c -o admin
	
ProtoBuffers.pb-c.c:
	$(PBC) $(PBCFLAGS) ProtoBuffers.proto

login_list.o:
	$(CC) -c -o login_list.o login_list.c

message.o:
	$(CC) -c -o message.o message.c

log.o: message.h
	$(CC) -c -o message.o message.c
 
server: ProtoBuffers.pb-c.c login_list.o
	$(CC) server.c login_list.c message.c ProtoBuffers.pb-c.c -l protobuf-c -o server.o $(PTHREADS)
	$(CC) -c -o server server.o login_list.o $(PTHREADS)

client: ProtoBuffers.pb-c.c
	$(CC) client.c message.c ProtoBuffers.pb-c.c -l protobuf-c -o client 

admin: ProtoBuffers.pb-c.c
	$(CC) admin.c message.c ProtoBuffers.pb-c.c -l protobuf-c -o admin

proto:
	$(PBC) $(PBCFLAGS) ProtoBuffers.proto