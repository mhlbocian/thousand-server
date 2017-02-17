#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>

#define TRUE 1
#define FALSE 0

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

int main(int argc, const char** argv) {
  int srvSock, cliSock, portNo;
  SOCKADDR_IN servAddr, cliAddr;
  socklen_t addrLen = sizeof(cliAddr);
  pid_t pid;

  srvSock = socket(AF_INET, SOCK_STREAM, 0);
  if (srvSock < 0) {
    perror("ERR socket creation failure");
    exit(1);
  }

  bzero((char*) &servAddr, sizeof(servAddr));
  portNo = 9900;
  
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = INADDR_ANY;
  servAddr.sin_port = htons(portNo);

  if (bind(srvSock, (SOCKADDR*) &servAddr, sizeof(servAddr)) < 0) {
    perror("ERR socket binding failure");
    exit(1);
  }

  listen(srvSock, 5);

  while (TRUE) {
      if((cliSock = accept(srvSock, (SOCKADDR*) &cliAddr, &addrLen)) < 0) {
          perror("ERR socket accepting from client failure");
          exit(1);
      }

      if ((pid = fork()) < 0) {
          perror("ERR socket listening fork failure");
          exit(1);
      }
      
      if (pid == 0) {
          close(srvSock);
          doprocessing(cliSock);
          exit(0);
      } else {
          close(cliSock);
      }
  }

  return 0;
}
