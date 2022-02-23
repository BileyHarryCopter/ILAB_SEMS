#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <locale.h>
#include "stdtext.h"
#include "Hamlet.h"



int main (void) {
    FILE * Hamlet;
    FILE * Hamlet_Begin;
    FILE * Hamlet_End;
    FILE * Poem;
    Hamlet = fopen ("Hamlet.txt", "r");
    Hamlet_Begin = fopen ("NewHamlet1.txt", "w");
    Hamlet_End = fopen ("NewHamlet2.txt", "w");
    Poem = fopen ("PoemHamlet.txt", "w");
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
    unsigned int nbytes = Bytesnumb (Hamlet);
    printf ("Number of bytes:   %u\n", nbytes);

    char * Buffer = Buffctor (nbytes);

    Freader (Buffer, nbytes, Hamlet);

    unsigned int nlines = Linesnumb (Buffer, nbytes);
    struct string * indexmass = Strinit (Buffer, nlines, nbytes);

//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                                 // SORTING
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
    Strsort (indexmass, nlines, BEGIN);
    Fprinter (indexmass, nlines, Hamlet_Begin, BEGIN);
    Strsort (indexmass, nlines, END);
    struct string * poemass = PulpGtor (indexmass, nlines, 8);
    Fprinter (poemass, 8, Poem, BEGIN);
    Fprinter (indexmass, nlines, Hamlet_End, END);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
    free (indexmass);
    free (poemass);
    free (Buffer);
    fclose (Hamlet);
    fclose (Hamlet_Begin);
    fclose (Hamlet_End);
    fclose (Poem);
    return 0;
}
