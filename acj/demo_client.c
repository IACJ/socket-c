/*
 * Create By IACJ - 2017/6/24
 *
 * Rewrite the code in COMPUTER NETWORKS Version 5 - p388 ~ P389
 * And make it runnable.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVER_PROT 2121
#define BUF_SIZE 4096

void fatal(char *str);
int main(int argc,char **argv){
    int c;
    int s;
    int bytes;
    char buf[BUF_SIZE];
    struct hostent *h;
    struct sockaddr_in channel;

    if (argc !=3){
        fatal("Usage: client server-name file-name");
    }
    h = gethostbyname(argv[1]);

}

void fatal(char *str){
    printf("%s\n",str);
    exit(1);
}