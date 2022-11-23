#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include <fcntl.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    close(STDIN_FILENO);                            // Prend valeur 0 : Cette ligne ferme entree standard
    int fd = open("toto.txt",O_RDONLY);
    exit_if(fd == -1, "Probleme d'ouverture");
    printf("Descripteur de fichier : %d\n",fd);
    return EXIT_SUCCESS;

}
