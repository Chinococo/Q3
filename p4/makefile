.PHONY: directories clean stat

all: build 

build: server.c client.c
	gcc  server.c -o server
	gcc  client.c -o client

directories:
	mkdir -p bin
clean:
	rm -rf bin 
