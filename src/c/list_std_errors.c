#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    fprintf(stderr, "ERROR CODE\tERROR MESSAGE\n");
    for(int i = 0; i < 255; ++i) {
        fprintf(stderr, "%10d\t%s\n", i, strerror(i));
    }
}
