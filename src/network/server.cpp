#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>

int main()
{
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(7575);
    local.sin_addr.s_addr = htonl( INADDR_ANY );

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if( s < 0 )
    {
        perror("socket call failed");
        exit(1);
    }

    int rc = bind(s, (struct sockaddr *)&local, sizeof(local));
    if( rc < 0 )
    {
        perror("bind call failed");
        exit(1);
    }
    rc = listen(s, 5);
    
    if( rc < 0 )
    {
        perror("listen call failed");
        exit(1);
    }

    int s1 = accept(s, NULL, NULL);
    
    if( s1  < 0 )
    {
        perror("accept call failed");
        exit(1);
    }

    char buf[1];
    rc = recv(s1, buf, 1, 0);

    if( rc <= 0 )
    {
        perror("recv call failed");
        exit(1);
    }

    printf("%c\n", buf[0]);
    rc = send(s1, "A", 1, 0);

    if( rc <= 0 )
    {
        perror("send call failed");
    }
    exit(0);
}