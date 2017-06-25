/*
 * Create By IACJ - 2017/6/25
 * Encoding:UTF-8
 *
 */

 #include <sys/types.h>
 #include <sys/fcntl.h>
 #include <sys/stat.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>
 #include <time.h>

 #include <string.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>

 #define SERVER_PORT 2121
 #define BUF_SIZE 4096
 #define QUEUE_SIZE 20

 void fatal(char *str);

 int main(int argc, char **argv){
    int s;
    int b;
    int l;
    int fd;
    int sa;
    int bytes;
    int on = 1;
    char buf[BUF_SIZE];
    char tmp[BUF_SIZE];
    struct sockaddr_in channel;
    time_t  ticks;  

    memset(&channel,0,sizeof(channel));
    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(SERVER_PORT);

    s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // use socket
    if (s < 0){
        fatal("[error]: socket failed!!!");
    }
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
    b =bind(s,(struct sockaddr *)&channel, sizeof(channel)); // use bind
    if (b < 0){
        fatal("[error]: bind failed!!!");
    }
    l = listen(s, QUEUE_SIZE); // use listen
    printf("\n[info]: listening...\n");
    while (1){
        printf("\n[info]: waiting for client connection...\n");
        sa = accept(s,0,0); // use accept
        if (sa < 0){
            fatal("[error]: accept failed!!!");
        }else{
            printf("\n[info]: got one connection...\n");
        }
        memset(buf,0,sizeof(char)*BUF_SIZE);
        read(sa,buf, BUF_SIZE);

        // time service
        if (strcasecmp(buf,"time")==0) {
            ticks = time(NULL);  
            memset(buf,0,sizeof(char)*BUF_SIZE);
            snprintf(buf, sizeof(buf), "[respons]: %.24s\r\n", ctime(&ticks));  
            write(sa, buf, strlen(buf)+1);  
            printf("[info]: time service done.\n");
            close(sa);
            printf("[info]: closed...\n\n");
            continue;
        }
        // talk service
        if (strcasecmp(buf,"whosyourdaddy")==0) {
            write(sa, "[respons]: IACJ\n", 17);  
            printf("[info]: talk service done.\n");
            close(sa);
            printf("[info]: closed...\n\n");
            continue;
        }
        if (strcasecmp(buf,"showmethemoney")==0) {
            write(sa, "[respons]: $$$$$$$$\n", 21);  
            printf("[info]: talk service done.\n");
            close(sa);
            printf("[info]: closed...\n\n");
            continue;
        }
        // command service
        if (strcasecmp(buf,"ls")==0) {

            FILE *fp;
            char ch;
            memset(buf,0,sizeof(char)*BUF_SIZE);
            fp = popen("ls -l ./FTP","r");
            while((ch=fgetc(fp))!=EOF) {
                strncat(buf,(char*)&ch,1);
            }

            write(sa, buf, strlen(buf)+1);  
            printf("[info]: command service done.\n");
            close(sa);
            printf("[info]: closed...\n\n");
            continue;
        }
        // FTP service
        if (strlen(buf) >5){
            memset(tmp,0,sizeof(char)*BUF_SIZE);
            strncpy(tmp,buf,5);
            if (strcasecmp(tmp,"file:")==0) {
                printf("[info]: FTP service : \"%s\"\n",buf+5); 

                // security
                if (strstr(buf+5,"../")){
                    printf("[warning]: \"../\" detected! \n");
                    write(sa, "[respons warning]: you can't do that!\n", 39); 
                    close(sa);
                    printf("[info]: closed...\n\n");
                    continue;
                }
                memset(tmp,0,sizeof(char)*BUF_SIZE);
                strcpy(tmp,"./FTP/");
                strcat(tmp,buf+5);
                fd = open(tmp, O_RDONLY);
                // file not found
                if (fd < 0){
                    printf("[info]: file not found.\n");
                    write(sa, "[error]: file not found!!!\n", 28);  
                    close(fd);
                    fd=0;
                    close(sa);
                    printf("[info]: closed...\n\n");
                    continue;
                }
                printf("[info]: sengding file...\n"); 
                while (1){
                    bytes = read(fd,buf,BUF_SIZE);
                    if (bytes <= 0){
                        printf("done...\n");
                        break;
                    }
                    write(sa,buf,bytes);
                }
                close(fd);
                close(sa);
                printf("[info]: closed...\n\n");
            }
        }
        printf("[info]: unknown intent. \n");
        write(sa, "[respons]: I don't know your intent.\n", 38);  
        close(sa);
        printf("[info]: closed...\n\n");
        continue;
    }
 }

void fatal(char *str){
    printf("%s\n",str);
    exit(1);
}