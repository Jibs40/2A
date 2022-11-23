#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include <fcntl.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    close(STDOUT_FILENO);                               // Prend valeur 0 : Cette ligne ferme entree standard
    int fd = open("test.txt",O_RDWR | O_APPEND | O_CREAT, 0644);      // O_APPEND permet d'ecrire à la fin du fichier, OCREAT permet de creer si existe pas avec mode a coté
    exit_if(fd == -1, "Probleme d'ouverture du fichier de destination");
    
    printf("J'ecris dans mon fichier\n");

    return EXIT_SUCCESS;    
}
