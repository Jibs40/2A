#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "utils.h"

/**
 *
 * Duplique le descripteur de la sortie standard (stdout) sur celui de la sortie
 * d'erreur (stderr).
 *
 * Redirige la sortie d'erreur et dans la sortie standard.
 * En shell: `ls / /toto 2>&1`
 */
int main(int argc, char *argv[])
{
    dup2(STDOUT_FILENO, STDERR_FILENO);
    execlp("ls", "ls", "/", "/toto", NULL);
    return 0;
}
