/*
 * Create By IACJ - 2017/6/25
 * Encoding:UTF-8
 *
 * Rewrite the code in COMPUTER NETWORKS Version 5 - p389 ~ P390
 * And make it runnable.
 */

 #include <sys/types.h>
 #include <sys/fcntl.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>

 #define SERBER_PORT 2121
 #define BUF_SIZE 4096
 #define QUEUE_SIZE 10

 int main(int argc, char **argv){
    int s;
    int b;
    int l;
    int fd;
    int sa;
    int bytes;
    int on = 1;
    char buf[BUF_SIZE];
    struct sockaddr_in channel;
    memset(&channel,0,sizeof(channel));
    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(SERVER_PORT);

    s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // use socket
    if (s < 0){
        fatal("socket failed");
    }
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
    b =bind(S,(struct sockaddr *)&channel, sizeof(channel));
    if (b < 0){
        fatal("bind failed!!!");
    }
    l = listen(s, QUEUE_SIZE); // use listen
    while (1){
        sa = accept(s,0,0); // use accept
        if (sa < 0){
            fatal("accept failed!!!");
        }
        read(sa,buf, BUF_SIZE);
        fd = open(buf, O_RDONLY);

        if (fd < 0){
            fatal("open failed!!!");
        }

        while (1){
            bytes = read(fd,buf,BUF_SIZE);
            if (bytes < 0){
                printf("done...");
                break;
            }
            write(sa,buf,bytes);
        }
        close(fd);
        close(sa);
    }
 }