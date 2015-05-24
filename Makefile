CC=gcc
PBC=protoc-c
PBCFLAGS =--c_out=.
PTHREADS=-lpthread
WALL=
G=-g

all: server client admin relauncher
	
ProtoBuffers.pb-c.c: ProtoBuffers.proto
	$(PBC) $(PBCFLAGS) ProtoBuffers.proto

ProtoBuffers.pb-c.o: ProtoBuffers.pb-c.c
	$(CC) -c -o ProtoBuffers.pb-c.o ProtoBuffers.pb-c.c

log.o: log.c message.h
	$(CC) -c -o log.o log.c $(G)

message.o: message.c ProtoBuffers.pb-c.o message.h
	$(CC) -c -o message.o message.c -l protobuf-c $(G)

login_list.o: login_list.c ProtoBuffers.pb-c.o message.o login_list.h
	$(CC) -c -o login_list.o login_list.c -l protobuf-c $(G)

server.o: server.c ProtoBuffers.pb-c.o message.o login_list.o log.o
	$(CC) -c -o server.o server.c -l protobuf-c $(PTHREADS) $(G)
 
server: server.o
	$(CC) $(WALL) -o server server.o message.o login_list.o log.o ProtoBuffers.pb-c.o -l protobuf-c $(PTHREADS) $(G)

client.o: client.c ProtoBuffers.pb-c.o message.o
	$(CC) -c -o client.o client.c -l protobuf-c $(PTHREADS) $(G)

client: client.o
	$(CC) $(WALL) -o client client.o message.o ProtoBuffers.pb-c.o -l protobuf-c $(PTHREADS) $(G)

admin.o: admin.c ProtoBuffers.pb-c.o message.o
	$(CC) -c -o admin.o admin.c -l protobuf-c $(PTHREADS) $(G)

admin: admin.o
	$(CC) $(WALL) -o admin admin.o message.o ProtoBuffers.pb-c.o -l protobuf-c $(PTHREADS) $(G)

relauncher.o: relauncher.c
	$(CC) -c -o relauncher.o relauncher.c $(PTHREADS) $(G)

relauncher: relauncher.o message.o ProtoBuffers.pb-c.o
	$(CC) $(WALL) -o relauncher relauncher.o message.o ProtoBuffers.pb-c.o -l protobuf-c $(PTHREADS) $(G)
