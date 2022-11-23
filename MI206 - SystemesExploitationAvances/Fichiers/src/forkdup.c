#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#include "utils.h"

#ifndef BUFFER_LEN
#       define BUFFER_LEN       5
#endif

/**
 * Met en evidence le partage des descripteurs apres un fork (héritage).
 * Un genre de `dup` interprocessus.
 */

int main(int argc, char *argv[])
{
    exit_if(argc < 2, "Syntax: ./forkdup <fichier>");
    int fd = open(argv[1], O_RDONLY);
    exit_if(fd == -1, "open");

    pid_t cpid = fork();
    exit_if(cpid == -1, "fork");

    unsigned char buffer[BUFFER_LEN + 1] = {};
    int read_len = read(fd, buffer, BUFFER_LEN);
    exit_if(read_len == -1, "read");
    buffer[read_len] = 0; // On va l'afficher avec "%s", on s'assure du 0 terminal

    printf("%s fd(%d) data len(%d): %s\n",
            (cpid == 0) ?  "child" : "father",
            fd, read_len, buffer);

    return EXIT_SUCCESS;
}
