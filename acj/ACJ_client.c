/*
 * Create By IACJ - 2017/6/25
 * Encoding:UTF-8
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 2121
#define BUF_SIZE 4096

void fatal(char *str);
void fatal_usage();

int main(int argc,char **argv){
    int c;
    int s;
    int bytes;
    char buf[BUF_SIZE];
    struct hostent *h;
    struct sockaddr_in channel;
    printf("\n");
    if (argc !=3 && argc !=4){
        fatal_usage();
    }
    
    h = gethostbyname(argv[1]);
    if (!h){
        fatal("[error]: get-host-name failed!!!");
    }
    s = socket(PF_INET, SOCK_STREAM,IPPROTO_TCP);  //use socket
    if (s < 0){
        fatal("[error]: socket-creating failed!!!");
    }
    memset(&channel, 0, sizeof(channel));
    channel.sin_family = AF_INET;
    memcpy(& channel.sin_addr.s_addr, h->h_addr, h->h_length);
    channel.sin_port = htons(SERVER_PORT);

    c = connect(s,(struct sockaddr *)&channel, sizeof(channel) ); //use connect
    if (c < 0) {
        fatal("[error]: connect failed!!!");
    }
    write(s, argv[2], strlen(argv[2])); //use write
    
    while (1){
        bytes = read(s,buf,BUF_SIZE);   /* use read */
        if (bytes <=0){
            printf("\n");
            exit(0);
        }
        write(1,buf,bytes);
    }
}

void fatal(char *str){
    printf("%s\n\n",str);
    exit(1);
}
void fatal_usage(){
    fatal("Usage: client server-name your-intent");
}