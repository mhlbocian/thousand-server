#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

void doprocessing(int sock) {
    int n;
    char buffer[512];
    bzero(buffer, sizeof(buffer));

    n = read(sock, buffer, sizeof(buffer));
    if (n < 0) {
        perror("ERR socket reading failure");
        exit(1);
    }

    printf("GET: %s; SND: ", buffer);

    n = write(sock, "Moja msg", 8);
    if (n < 0) {
        perror("ERR socket writing failure");
        exit(1);
    }
}
