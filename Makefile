client :
	cc client.c -o client && ./client

server :
	cc server.c -o server && ./server

clean :
	rm client server
