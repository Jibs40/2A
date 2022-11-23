#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "utils.h"

/**
 * Filtre les `a` de son entrée standard et les écrits sur sa sortie standard
 */

int main(int argc, char *argv[])
{
    char buffer[100];
    char output[100];
    char letterstoremove[100];
int r;

    while((r = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        int out_len = 0;
        for (int i = 0; i < r; i ++)
            if (buffer[i] != &argv[i])
                output[out_len ++] = buffer[i];
        exit_if(
                write(STDOUT_FILENO, output, out_len) == -1, "write");
    }
    return !!r;
}
