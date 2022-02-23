#include <stdio.h>
#include <stdlib.h>
#include "stdtext.h"
#include <assert.h>
#include <string.h>


struct lab {
    double b;
    double c;
    char string[];
};

struct lab mas = {
    12.2,
    23e-10,
    "srtfiiad",
};

int main () {

    char string[20];

    char string1[] = "Poltor";
    char string2[] = "ashka";
    printf ("%s\n", strcatFRM (string1, string2));

    /*
    FILE * PtrFile = fopen ("textforfile.txt", "w"); // fopen возвращает указатель объекта файла

    if (PtrFile != NULL) {
        fputs("Fuck you and all of your fucking family!\n", PtrFile);
        fclose(PtrFile); //  закрывает по указателю
    }
    */

    /*
    FILE * PtrFile = fopen ("textforfile.txt", "r");

    fgetsFRM (string, sizeof(string), PtrFile); // считывает до \n
    printf ("%s\n", string);

    assert (string != NULL);
    */
    return 0;
}
