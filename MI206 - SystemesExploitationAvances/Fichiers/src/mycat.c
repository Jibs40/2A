#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include <fcntl.h>

#include "utils.h"


int main(int argc, char *argv[])
{
    exit_if(argc<3, " Syntax : ./redir <fichier> <cmd> [...]");
    exit_if(close(STDOUT_FILENO) == -1, "close");                            // Prend valeur 0 : Cette ligne ferme entree standard
    int fd = open(argv[1],O_WRONLY | O_APPEND | O_CREAT, 0644);
    exit_if(fd == -1 ,"Not open");
    argv += 2;
    argc -= 2;
    execvp(argv[0],argv);                                                   // execvp permet de s'affranchir de taper le chemin de la cmd, par ex ls au lieu de /bin/ls
    exit_if(1,"Exec");

    return EXIT_SUCCESS;

}
