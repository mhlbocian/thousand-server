CC = "gcc"

thousand-server: game.c athousand-server.c
	$(CC) -Wall -o thousand-server game.c athousand-server.c
