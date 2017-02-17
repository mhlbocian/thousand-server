CC = "gcc"

thousand-server: game.c thousand-server.c
	$(CC) -Wall -o thousand-server game.c thousand-server.c
