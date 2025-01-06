// #include "unp.h"

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
// #include	<sys/time.h>	/* timeval{} for select() */
// #include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<unistd.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
// #include <iostream>
// #include <array>
#define	MAXLINE		4096	/* max text line length */
#define	SA	struct sockaddr

int main(int argc, char *argv[])
{
    int sockfd, n;
    // std::array<char, MAXLINE+1> recvline;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if( argc != 2 )
    {
        printf("Usage: daytime-server <IP-Address>");
        exit(-1);
    }

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket() error");
        exit(-1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2013);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        printf("inet_pton() error for %s", argv[1]);
        exit(-1);
    }

    if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect() error");
        exit(-1);
    }

    while( (n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        printf("rx: %s\n", recvline);
        // std::cout << recvline << std::endl;
    }
    if(n < 0)
    {
        printf("read error");
    }
    exit(0);
}