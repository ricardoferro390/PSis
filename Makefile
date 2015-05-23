CC=gcc
PBC=protoc-c
PBCFLAGS =--c_out=.
PTHREADS=-lpthread

all: server client admin
	
ProtoBuffers.pb-c.c: ProtoBuffers.proto
	$(PBC) $(PBCFLAGS) ProtoBuffers.proto

ProtoBuffers.pb-c.o: ProtoBuffers.pb-c.c
	$(CC) -c -o ProtoBuffers.pb-c.o ProtoBuffers.pb-c.c

log.o: log.c
	$(CC) -c -o log.o log.c

message.o: message.c ProtoBuffers.pb-c.o
	$(CC) -c -o message.o message.c -l protobuf-c

login_list.o: login_list.c ProtoBuffers.pb-c.o message.o login_list.h
	$(CC) -c -o login_list.o login_list.c -l protobuf-c

server.o: server.c ProtoBuffers.pb-c.o message.o login_list.o log.o
	$(CC) -c -o server.o server.c -l protobuf-c $(PTHREADS)
 
server: server.o
	$(CC) $(Wall) -o server server.o message.o login_list.o log.o ProtoBuffers.pb-c.o -l protobuf-c $(PTHREADS)

client.o: client.c ProtoBuffers.pb-c.o message.o
	$(CC) -c -o client.o client.c -l protobuf-c $(PTHREADS)

client: client.o
	$(CC) $(Wall) -o client client.o message.o ProtoBuffers.pb-c.o -l protobuf-c $(PTHREADS)

admin.o: admin.c ProtoBuffers.pb-c.o message.o
	$(CC) -c -o admin.o admin.c -l protobuf-c $(PTHREADS)

admin: admin.o
	$(CC) $(Wall) -o admin admin.o message.o ProtoBuffers.pb-c.o -l protobuf-c $(PTHREADS)
