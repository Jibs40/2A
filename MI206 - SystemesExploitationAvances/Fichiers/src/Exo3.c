#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include <fcntl.h>

#include "utils.h"
#define BUFFER_LEN 1

int main(int argc, char *argv[])
{
    char *buff;
    int fd;
    exit_if(read(STDIN_FILENO,buff,BUFFER_LEN) == -1 , "Read Error");
    fd = open("dest.txt",O_RDWR|O_CREAT , 0624);
    exit_if(fd == -1,"Open Error");
    exit_if(write(fd,buff,BUFFER_LEN) == -1,"Write Error");

    return EXIT_SUCCESS;    
}
